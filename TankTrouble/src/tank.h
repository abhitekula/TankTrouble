#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Tank : public ofxBox2dPolygon {

  // Constants
  const string kBulletFilename = "data/bullet.txt";
  const int kStartingAmmo = 5;
  const double kStartingHealth = 1;
  const double kRefillInterval = 10; // How often to refill ammo in seconds
  const double kBulletDamage = 0.5;  // How much damage each bullet does
  const double kBulletVelocity = 8;

private:
  typedef ofxBox2dPolygon super; //Allows for call to super.draw()

  vector<ofPoint> loadPoints(string file);
  void *createTank(string file, b2World *world);

  int ammo_;
  int id_;
  double health_;
  vector<ofxBox2dCircle *> bullets_;

public:
  Tank(int id, string file, b2World *world); // Initalize from file

  int getAmmo();

  int getId();

  double getHealth();

  bool isDead();

  void draw();

  void hit();

  void reset();

  void shoot(b2World *world);
};