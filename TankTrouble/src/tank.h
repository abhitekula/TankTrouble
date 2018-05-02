#pragma once

#include <math.h>
#include "ofMain.h"
#include "ofxBox2d.h"

class Tank : public ofxBox2dPolygon {

  // Constants
  const string kBulletFilename = "data/bullet.txt";
  const int kStartingAmmo = 5;
  const double kStartingHealth = 1;
  const double kStartingLinearVelocity = 10;
  const double kStartingAngularVelocity = 3;
  const double kBulletDamage = 0.5;  // How much damage each bullet does
  const double kStartingBulletVelocity = 11;
  const double kBulletDistanceFromTank = 130;
  const double kDamping = 1.5;

private:
  typedef ofxBox2dPolygon super; //Allows for call to super.draw()
  int ammo_;
  double health_;
  double linear_velocity_;
  double angular_velocity_;
  double bullet_velocity_;
  vector<ofxBox2dCircle *> bullets_;

  void *createTank(string file, b2World *world);

  static vector<ofPoint> loadPoints(string file);

  void removeBullets(); //To remove the bullets that hit the tank

public:
  Tank(string file, b2World *world); // Initalize from file

  int getAmmo();

  int getId();

  double getHealth();

  vector<ofxBox2dCircle *> getBullets();

  double getLinearVelocity();

  double getAngularVelocity();

  double getBulletVelocity();

  void addAmmo(int amount);

  void setHealth(double health);

  void setLinearVelocity(double velocity);

  void setAngularVelocity(double velocity);

  void setBulletVelocity(double velocity);

  bool isDead();

  void draw();

  void hit();

  void reset();

  void shoot(b2World *world);
};