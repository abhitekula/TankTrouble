#include "collisionDetector.h"
#include "tank.h"

void CollisionDetector::BeginContact(b2Contact *contact) {
  cout << "Collision Detected\n";
  auto bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
  auto bodyB = contact->GetFixtureB()->GetBody()->GetUserData();

  if (static_cast<Tank*>(bodyA)) {
      cout << "Fixture A is a tank\n";
  }
  if (static_cast<Tank*>(bodyB)) {
      cout << "Fixture B is a tank\n";
  }
}