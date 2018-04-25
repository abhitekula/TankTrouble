#pragma once

#include "collisionDetector.h"
#include "ofMain.h"
#include "ofxBox2d.h"
#include "tank.h"

class ofApp : public ofBaseApp {

  // Constants
  const string kDefaultTankFilename = "data/tank.txt";
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
  const int kP2Shoot = OF_KEY_PAGE_DOWN;

private:
  bool isKeyPressed[255];
  bool is_round_over;
  Tank *p1_tank;
  Tank *p2_tank;
  ofxBox2d box2d;
  int p1_score_ = 0;
  int p2_score_ = 0;

  void setupTanks();

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
