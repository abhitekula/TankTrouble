#pragma once

#include "collisionDetector.h"
#include "maze.h"
#include "ofMain.h"
#include "ofxBox2d.h"
#include "tank.h"
#include <math.h>

class ofApp : public ofBaseApp {

  // Constants
  const string kDefaultTankFilename = "data/tank.txt";
  const string kStartupSoundFilename = "data/sounds/startup2.mp3";
  const string kMazeEdgesFilename = "data/mazes/maze";
  const string kMazePositionsFilename = "data/mazes/maze";
  const int kNumMazes = 2;
  const double kLinearVelocity = 10;
  const double kAngularVelocity = 3;
  const double kDamping = 1.5;
  const int kP1Forward = 'W';
  const int kP1Backward = 'S';
  const int kP1Right = 'D';
  const int kP1Left = 'A';
  const int kP1Shoot = 'E';
  const int kP2Forward = OF_KEY_UP;
  const int kP2Backward = OF_KEY_DOWN;
  const int kP2Right = OF_KEY_RIGHT;
  const int kP2Left = OF_KEY_LEFT;
  const int kP2Shoot = '/'; // OF_KEY_PAGE_DOWN
  const int kFPS = 30;

private:
  bool is_key_pressed_[255];
  bool is_round_over_;
  bool paused_ = false;
  ofxBox2d box2d_;
  Tank *p1_tank_;
  Tank *p2_tank_;
  int p1_score_ = 0;
  int p2_score_ = 0;
  ofSoundPlayer *startup_sound_player_;
  vector<Maze*> mazes_;
  Maze *current_maze_;

  void setupTanks();

  void setupMazes();

  void updateTanks();

  void reset();

public:
  void setup();

  void update();

  void draw();

  void keyPressed(int key);

  void keyReleased(int key);

  void mouseMoved(int x, int y);

  void mouseDragged(int x, int y, int button);

  void mousePressed(int x, int y, int button);

  void mouseReleased(int x, int y, int button);

  void mouseEntered(int x, int y);

  void mouseExited(int x, int y);

  void windowResized(int w, int h);

  void dragEvent(ofDragInfo dragInfo);

  void gotMessage(ofMessage msg);
};
