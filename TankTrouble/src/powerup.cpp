#include "powerup.h"

Powerup::Powerup(b2World *world) {
  createPowerup(world);
  setupSound();
  body->SetUserData(this); // For the collision detection
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

void Powerup::setupSound() {
  sound_ = new ofSoundPlayer();
  sound_->setMultiPlay(true);
  string filename;

  switch (type_) {
  case kSpeed:
    filename = "data/sounds/speed.mp3";
    break;
  case kAmmo:
    filename = "data/sounds/ammo.mp3";
    break;
  case kBulletSpeed:
    filename = "data/sounds/bullet.mp3";
    break;
  case kHealth:
    filename = "data/sounds/health.mp3";
    break;
  }

  sound_->load(filename);
}

Powerup::~Powerup() {
  destroy();
  delete sound_;
}

Powerup::Power Powerup::getType() { return type_; }

int Powerup::getColor() {
  switch (type_) {
  case kSpeed:
    return kOrange;
    break;
  case kAmmo:
    return kYellow;
    break;
  case kBulletSpeed:
    return kPurple;
    break;
  case kHealth:
    return kGreen;
    break;
  }
}

void Powerup::usePowerup(Tank *tank) {
  sound_->play();
  switch (type_) {
  case kSpeed:
    tank->setLinearVelocity(kNewLinearVelocity);
    tank->setAngularVelocity(kNewAngularVelocity);
    tank->setBulletVelocity(kNewBulletVelocity);
    break;
  case kAmmo:
    tank->setAmmo(kAmmoRefill);
    break;
  case kBulletSpeed:
    tank->setBulletVelocity(kNewBulletVelocity);
    break;
  case kHealth:
    tank->setHealth(kNewHealth);
    break;
  }
}