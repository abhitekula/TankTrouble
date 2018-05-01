#include "tank.h"

Tank::Tank(int id, string file, b2World *world) {
  id_ = id;
  health_ = kStartingHealth;
  ammo_ = kStartingAmmo;

  createTank(file, world);
  body->SetUserData(this);
}

void *Tank::createTank(string file, b2World *world) {
  b2BodyDef tank_body_def;
  tank_body_def.type = b2_dynamicBody;
  b2Body *tank_body = world->CreateBody(&tank_body_def);

  b2PolygonShape rectangle;
  rectangle.SetAsBox(0, 0, b2Vec2(0, 0), 0);

  b2FixtureDef tank_fixture;
  tank_fixture.shape = &rectangle;
  tank_fixture.density = 1;

  tank_body->CreateFixture(&tank_fixture);

  vector<ofPoint> tank_pts = loadPoints(file);
  addVertices(tank_pts);
  triangulatePoly();
  body = tank_body;
  create(world);
  setPhysics(0.7, 0.5, 0.5);
  body->SetBullet(true);
  body->SetType(b2_dynamicBody);
  body->SetLinearDamping(kDamping);
  body->SetAngularDamping(kDamping);
}

vector<ofPoint> Tank::loadPoints(string file) {
  vector<ofPoint> points;
  float x;
  float y;

  ifstream inputFile;
  inputFile.open(file);

  if (inputFile.is_open()) {
    while (!inputFile.eof()) {
      inputFile >> x;
      inputFile >> y;
      points.push_back(ofPoint(x, y));
    }
  }

  inputFile.close();
  return points;
}

int Tank::getAmmo() { return ammo_; }

int Tank::getId() { return id_; }

double Tank::getHealth() { return health_; }

vector<ofxBox2dCircle *> Tank::getBullets() { return bullets_; }

bool Tank::isDead() { return health_ <= 0; }

void Tank::hit() { health_ -= kBulletDamage; }

void Tank::reset() {
  for (auto bullet : bullets_) {
    if (bullet) {
      bullet->destroy();
    }
  }
  bullets_.clear();
  body->SetLinearVelocity(b2Vec2(0, 0));
  body->SetAngularVelocity(0);
  health_ = kStartingHealth;
  ammo_ = kStartingAmmo;
}

void Tank::shoot(b2World *world) {
  if (ammo_ > 0) {
    ammo_--;
    ofxBox2dCircle *bullet = new ofxBox2dCircle();

    b2BodyDef bullet_body_def;
    bullet_body_def.type = b2_dynamicBody;
    b2Body *bullet_body = world->CreateBody(&bullet_body_def);
    bullet->setPhysics(1, 1, 0); // Density, Bounce, Friction
    bullet->setDamping(0);
    bullet->body = bullet_body;
    bullet->body->SetType(b2_dynamicBody);
    bullet->body->SetBullet(true);

    double tank_angle = this->body->GetAngle();
    bullet->setup(
        world,
        this->getPosition().x + kBulletDistanceFromTank * sin(tank_angle),
        this->getPosition().y + kBulletDistanceFromTank * -cos(tank_angle), 10);
    bullet->setRotation(this->getRotation());
    double angle = (bullet->body->GetAngle());
    bullet->setVelocity(sin(angle) * kBulletVelocity,
                        -cos(angle) * kBulletVelocity);
    bullet->body->SetUserData(bullet);
    bullets_.push_back(bullet);
  }
}

void Tank::draw() {
  super::draw();
  removeBullets();
  for (auto bullet : bullets_) {
    bullet->draw();
  }
}

void Tank::removeBullets() {
  vector<int> indexes_to_remove;
  for(int i = 0; i < bullets_.size(); i++) {
    if(!bullets_[i]->body->GetUserData()) {
      indexes_to_remove.push_back(i);
    }
  }

  for(auto i: indexes_to_remove) {
    bullets_[i]->destroy();
    bullets_.erase(bullets_.begin() + i);
  }
}