#include "collisionDetector.h"

void CollisionDetector::BeginContact(b2Contact *contact) {
  if (first_contact_) {
    setup();
  }

  Tank *tank = nullptr;
  ofxBox2dCircle *bullet = nullptr;

  cout << "Collision Detected\n";

  auto bodyA = static_cast<ofxBox2dBaseShape *>(
      contact->GetFixtureA()->GetBody()->GetUserData());
  auto bodyB = static_cast<ofxBox2dBaseShape *>(
      contact->GetFixtureB()->GetBody()->GetUserData());

  if (dynamic_cast<Tank *>(bodyA)) {
    cout << "Fixture A is a tank\n";
    tank = dynamic_cast<Tank *>(bodyA);
  }

  if (dynamic_cast<Tank *>(bodyB)) {
    cout << "Fixture B is a tank\n";
    tank = dynamic_cast<Tank *>(bodyB);
  }

  if (dynamic_cast<ofxBox2dCircle *>(bodyA)) {
    cout << "Fixture A is an bullet\n";
    bounce_sound_->play();
    bullet = dynamic_cast<ofxBox2dCircle *>(bodyA);
  }

  if (dynamic_cast<ofxBox2dCircle *>(bodyB)) {
    cout << "Fixture B is an bullet\n";
    bounce_sound_->play();
    bullet = dynamic_cast<ofxBox2dCircle *>(bodyB);
  }

  if (tank && bullet) {
    cout << "Tank " << tank->getId() << " is Hit!!!" << endl;
    tank->hit();
  }
}

void CollisionDetector::setup() {
  first_contact_ = false;
  bounce_sound_ = new ofSoundPlayer();
  bounce_sound_->setMultiPlay(true);
  bounce_sound_->load(kBounceSoundFilename);
}