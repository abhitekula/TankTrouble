#include "tank.h"

Tank::Tank(string file, b2World *world) {
  createTank(file, world);
  ammo = kStartingAmmo;
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
  setPhysics(0.7, 0.5, 0.5);
  triangulatePoly();
  body = tank_body;
  body->SetType(b2_dynamicBody);
  create(world);
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

int Tank::getAmmo() { return ammo; }

void Tank::shoot(b2World *world) {
  ofxBox2dPolygon *bullet = new ofxBox2dPolygon();
  bullets.push_back(bullet);

  b2BodyDef bullet_body_def;
  bullet_body_def.type = b2_dynamicBody;
  b2Body *bullet_body = world->CreateBody(&bullet_body_def);

  vector<ofPoint> bullet_pts = loadPoints(kBulletFilename);
  bullet->addVertices(bullet_pts);
  bullet->setPhysics(0.7, 0.5, 0.5);
  bullet->body = bullet_body;
  bullet->body->SetType(b2_dynamicBody);
  bullet->create(world);

  bullet->setPosition(this->getPosition().x + 50, this->getPosition().y - 100);
  bullet->setRotation(this->getRotation());
  double angle = (bullet->body->GetAngle());
  bullet->setVelocity(sin(angle) * kBulletVelocity, -cos(angle) * kBulletVelocity);
}

void Tank::draw() {
    super::draw();
    for (auto bullet : bullets) {
        bullet->draw();
    }
}