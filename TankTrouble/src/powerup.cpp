#include "powerup.h"

Powerup::Powerup(b2World *world) {
  createPowerup(world);
  setupSound();
  body->SetUserData(this); // For the collision detection
}

void Powerup::createPowerup(b2World *world) {
  int x = rand() % kPowerupSpanXCoordinates + kPowerupStartingXCoordinate;
  int y = rand() % kPowerupSpanYCoordinates + kPowerupStartingYCoordinate;
  setup(world, x, y, kRectSize, kRectSize);
  setPhysics(kDensity, kBounce, kFriction); // Density, Bounce, Friction
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
    filename = kSpeedFilename;
    break;
  case kAmmo:
    filename = kAmmoFilename;
    break;
  case kBulletSpeed:
    filename = kBulletSpeedFilename;
    break;
  case kHealth:
    filename = kHealthFilename;
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