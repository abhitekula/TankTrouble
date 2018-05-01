#include "powerup.h"

Powerup::Powerup(b2World *world) {
  createPowerup(world);
  body->SetUserData(this); //For the collision detection
}

void Powerup::createPowerup(b2World *world) {
  int x = rand() % 1800 + 60;
  int y = rand() % 900 + 90;
  setup(world, x, y, kRectSize, kRectSize);
  setPhysics(5, 0.5, 0.5);
  body->SetType(b2_dynamicBody);
  body->SetLinearDamping(kDamping);
  body->SetAngularDamping(kDamping);  
  
  type_ = Power(rand() % numPowerupTypes);
}

Powerup::~Powerup() {
  destroy();
}

Powerup::Power Powerup::getType() {
  return type_;
}