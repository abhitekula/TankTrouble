#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Maze {

  // Constants

private:
  vector<ofxBox2dEdge *> maze_edges_;

  void* createMaze(string file, b2World *world);

  static vector<ofVec2f> loadPoints(string file);

public:
  Maze(string file, b2World *world); // Initalize from file

  void draw();
};