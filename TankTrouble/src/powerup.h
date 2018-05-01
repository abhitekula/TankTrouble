#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class Powerup : public ofxBox2dRect {

  // Constants
  const int kRectSize = 30;
  enum Power { kSpeed, kAmmo, kBulletSpeed };
  const int numPowerupTypes = 3;

private:
  typedef ofxBox2dPolygon super; // Allows for call to super.draw()
  Power type_;

  void createPowerup(b2World *world);

public:
  Powerup(b2World *world);

  ~Powerup();

  Power getType();
};