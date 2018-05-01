#include "powerup.h"

Powerup::Powerup(b2World *world) {
  createPowerup(world);
}

void Powerup::createPowerup(b2World *world) {
  int x = rand() % 1800 + 60;
  int y = rand() % 900 + 90;
  setup(world, x, y, kRectSize, kRectSize);
  
  type_ = Power(rand() % numPowerupTypes);
}

Powerup::~Powerup() {
  destroy();
}

Powerup::Power Powerup::getType() {
  return type_;
}