#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class Powerup : public ofxBox2dRect {

  // Constants
  const int kRectSize = 30;
  enum Power { kSpeed, kAmmo, kBulletSpeed };
  enum Color { kOrange = 0xCC6600, kYellow = 0xCCCC00, kPurple = 0x4C0099};
  const int numPowerupTypes = 3;
  const double kDamping = 5;

private:
  Power type_;

  void createPowerup(b2World *world);

public:
  Powerup(b2World *world);

  ~Powerup();

  Power getType();

  int getColor();
};