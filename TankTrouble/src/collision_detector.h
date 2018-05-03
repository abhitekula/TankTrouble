#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "tank.h"
#include "powerup.h"

class CollisionDetector : public b2ContactListener {

  // Constants
  const string kBounceSoundFilename = "data/sounds/bounce.mp3";

private:
  bool first_contact_ = true;
  ofSoundPlayer *bounce_sound_;

  void setup();

public:
  void BeginContact(b2Contact *contact); //Overridden Method
};