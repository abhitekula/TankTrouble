#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "tank.h"

class CollisionDetector : public b2ContactListener {

public:
  void BeginContact(b2Contact *contact);
};