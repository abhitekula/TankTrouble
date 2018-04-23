#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Tank : public ofxBox2dPolygon {
	
	//Constants
	

private:
  vector<ofPoint> loadPoints(string file);
  void *createTank(string file, b2World *world);

//   ofxBox2d box2d;

public:
  Tank(string file, b2World *world); // Initalize from file
};