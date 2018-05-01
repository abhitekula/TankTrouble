#include "collisionDetector.h"

void CollisionDetector::BeginContact(b2Contact *contact) {
  if (first_contact_) {
    setup();
  }

  Tank *tank = nullptr;
  ofxBox2dCircle *bullet = nullptr;

  auto bodyA = static_cast<ofxBox2dBaseShape *>(
      contact->GetFixtureA()->GetBody()->GetUserData());
  auto bodyB = static_cast<ofxBox2dBaseShape *>(
      contact->GetFixtureB()->GetBody()->GetUserData());

  if (dynamic_cast<Tank *>(bodyA)) {
    tank = dynamic_cast<Tank *>(bodyA);
  }

  if (dynamic_cast<Tank *>(bodyB)) {
    tank = dynamic_cast<Tank *>(bodyB);
  }

  if (dynamic_cast<ofxBox2dCircle *>(bodyA)) {
    bounce_sound_->play();
    bullet = dynamic_cast<ofxBox2dCircle *>(bodyA);
  }

  if (dynamic_cast<ofxBox2dCircle *>(bodyB)) {
    bounce_sound_->play();
    bullet = dynamic_cast<ofxBox2dCircle *>(bodyB);
  }

  if (tank && bullet) {
    tank->hit();
    bullet->body->SetUserData(nullptr);
  }

  if (dynamic_cast<Powerup *>(bodyA)) {
    cout << "Powerup Collision Detected" << endl;
  }

  if (dynamic_cast<Powerup *>(bodyB)) {
    cout << "Powerup Collision Detected" << endl;
  }
}

void CollisionDetector::setup() {
  first_contact_ = false;
  bounce_sound_ = new ofSoundPlayer();
  bounce_sound_->setMultiPlay(true);
  bounce_sound_->load(kBounceSoundFilename);
}