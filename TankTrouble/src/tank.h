#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include <math.h>

class Tank : public ofxBox2dPolygon {

  // Constants
  const string kBulletFilename = "data/bullet.txt";
  const double kTankDensity = 0.7;
  const double kTankBounce = 0.5;
  const double kTankFriction = 0.5;
  const int kStartingAmmo = 5;
  const double kStartingHealth = 1;
  const double kStartingLinearVelocity = 10;
  const double kStartingAngularVelocity = 3;

  const double kBulletDensity = 1;
  const double kBulletBounce = 1;
  const double kBulletFriction = 0;
  const double kBulletDamage = 0.5; // How much damage each bullet does
  const double kStartingBulletVelocity = 11;
  const double kBulletDistanceFromTank = 130;
  const int kBulletSize = 10;
  const double kDamping = 1.5;

  const string kTankHitSoundFilename = "data/sounds/tankHit.mp3";
  const string kTankDeadSoundFilename = "data/sounds/tankDead.mp3";
  const string kShootSoundFilename = "data/sounds/shoot.mp3";

private:
  typedef ofxBox2dPolygon super; // Allows for call to super.draw()
  int ammo_;
  double health_;
  double linear_velocity_;
  double angular_velocity_;
  double bullet_velocity_;
  vector<ofxBox2dCircle *> bullets_;
  ofSoundPlayer *hit_sound_;
  ofSoundPlayer *destroyed_sound_;
  ofSoundPlayer *shoot_sound_;

  void *createTank(string file, b2World *world);

  static vector<ofPoint> loadPoints(string file);

  void loadSounds();

  void removeBullets(); // To remove the bullets that hit the tank

public:
  Tank(string file, b2World *world); // Initalize from file

  int getAmmo();

  int getId();

  double getHealth();

  vector<ofxBox2dCircle *> getBullets();

  double getLinearVelocity();

  double getAngularVelocity();

  double getBulletVelocity();

  void setAmmo(int amount);

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