#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "tank.h"

class Powerup : public ofxBox2dRect {

  // Constants
  const int kRectSize = 30;
  const double kDamping = 5;
  const double kDensity = 5;
  const double kBounce = 0.5;
  const double kFriction = 0.5;

  const int kPowerupStartingXCoordinate = 60;
  const int kPowerupSpanXCoordinates =
      1800; // Over what distance will the powerups spawn x direction
  const int kPowerupStartingYCoordinate = 90;
  const int kPowerupSpanYCoordinates =
      900; // Over what distance will the powerups spawn y direction

  enum Power { kSpeed, kAmmo, kBulletSpeed, kHealth };
  enum Color {
    kOrange = 0xCC6600,
    kYellow = 0xCCCC00,
    kPurple = 0x4C0099,
    kGreen = 0x00FF00
  };

  const int numPowerupTypes = 4;
  const int kAmmoRefill = 5;
  const double kNewLinearVelocity = 15;
  const double kNewAngularVelocity = 5;
  const double kNewBulletVelocity = 20;
  const double kNewHealth = 1;

  const string kSpeedFilename = "data/sounds/speed.mp3";
  const string kAmmoFilename = "data/sounds/ammo.mp3";
  const string kBulletSpeedFilename = "data/sounds/bullet.mp3";
  const string kHealthFilename = "data/sounds/health.mp3";

private:
  Power type_;
  ofSoundPlayer *sound_;

  void createPowerup(b2World *world);

  void setupSound();

public:
  Powerup(b2World *world);

  ~Powerup();

  Power getType();

  int getColor();

  void usePowerup(Tank *tank);
};