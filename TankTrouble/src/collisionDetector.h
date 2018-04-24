#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class CollisionDetector : public b2ContactListener {

  // Constants

public:
  void BeginContact(b2Contact* contact);
};