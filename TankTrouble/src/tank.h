#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Tank : public ofxBox2dPolygon {

  // Constants
  const string kBulletFilename = "data/bullet.txt";
  const int kStartingAmmo = 5;
  const double kRefillInterval = 10; // How often to refill ammo in seconds
  const double kBulletDamage = 0.5;  // How much damage each bullet does
  const double kBulletVelocity = 8;

private:
  typedef ofxBox2dPolygon super;

  vector<ofPoint> loadPoints(string file);
  void *createTank(string file, b2World *world);

  int ammo;
  int id_;
  double health;
  vector<ofxBox2dCircle *> bullets;

public:
  Tank(int id, string file, b2World *world); // Initalize from file

  int getAmmo();

  int getId();

  void draw();

  void shoot(b2World *world);
};