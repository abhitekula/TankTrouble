#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "tank.h"

class Powerup : public ofxBox2dRect {

  // Constants
  const int kRectSize = 30;
  enum Power { kSpeed, kAmmo, kBulletSpeed, kHealth };
  enum Color {
    kOrange = 0xCC6600,
    kYellow = 0xCCCC00,
    kPurple = 0x4C0099,
    kGreen = 0x00FF00
  };
  const int numPowerupTypes = 4;
  const double kDamping = 5;
  const int kAmmoToAdd = 3;
  const double kNewLinearVelocity = 15;
  const double kNewAngularVelocity = 5;
  const double kNewBulletVelocity = 20;
  const double kNewHealth = 1;

private:
  Power type_;
  ofSoundPlayer* sound_;

  void createPowerup(b2World *world);

  void setupSound();

public:
  Powerup(b2World *world);

  ~Powerup();

  Power getType();

  int getColor();

  void usePowerup(Tank *tank);
};