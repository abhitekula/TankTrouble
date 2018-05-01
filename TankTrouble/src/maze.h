#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Maze {

  // Constants
  const string kEdgeDelimiter = "edge";

private:
  vector<ofxBox2dEdge *> maze_edges_;
  vector<ofVec2f> p1_starting_positions_;
  vector<ofVec2f> p2_starting_positions_;

  void createMaze(string file, b2World* world);

  static vector<ofVec2f> loadMazes(string file);

  ofxBox2dEdge* createEdge(vector<ofVec2f> points, b2World* world);

  void loadStartingPositions(string file);

public:
  Maze(string edge_file, string positions_file, b2World* world); // Initalize from file

  ~Maze(); // Initalize from file

  void draw();

  ofVec2f getStartingPosition(bool player_one);
};