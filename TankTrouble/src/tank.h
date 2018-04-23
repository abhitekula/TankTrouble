#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Tank : public ofxBox2dPolygon {

  // Constants
  const int kStartingAmmo = 5;
  const double kRefillInterval = 10; // How often to refill ammo in seconds
  const double kBulletDamage = 0.5; // How much damage each bullet does

private:
  vector<ofPoint> loadPoints(string file);
  void *createTank(string file, b2World *world);
  int ammo;
  double health;

public:
  Tank(string file, b2World *world); // Initalize from file

  int getAmmo();

  void shoot();
};