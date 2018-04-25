#include "collisionDetector.h"

void CollisionDetector::BeginContact(b2Contact *contact) {
  cout << "Collision Detected\n";
  auto bodyA = static_cast<ofxBox2dBaseShape *>(contact->GetFixtureA()->GetBody()->GetUserData());
  auto bodyB = static_cast<ofxBox2dBaseShape *>(contact->GetFixtureB()->GetBody()->GetUserData());

  if (dynamic_cast<Tank *>(bodyA)) {
    cout << "Fixture A is a tank\n";
  }
  if (dynamic_cast<Tank *>(bodyB)) {
    cout << "Fixture B is a tank\n";
  }

  if (dynamic_cast<ofxBox2dCircle *>(bodyA)) {
    cout << "Fixture A is an bullet\n";
  }
  if (dynamic_cast<ofxBox2dCircle *>(bodyB)) {
    cout << "Fixture B is an bullet\n";
  }
}