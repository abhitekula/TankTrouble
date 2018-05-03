#pragma once

#include "collision_detector.h"
#include "maze.h"
#include "ofMain.h"
#include "ofxBox2d.h"
#include "tank.h"
#include "powerup.h"
#include <math.h>

class ofApp : public ofBaseApp {

    // Constants
    const int kFPS = 30;
    const double kPowerupChance = 3; //Chance that new powerup spawns

    const int kBackgroundColor = 0xfdefc2;
    const int kBlack = 0x000000;
    const int kRed = 0xFF0000;
    const int kBlue = 0x0000FF;

    const int kScoreXPosition = 0;
    const int kScoreYPosition = 20;
    const int kFpsXPosition = 100; //From right of screen
    const int kFpsYPosition = 20;
    const int kP1StatusXPosition = 50;
    const int kP1StatusYPosition = 20; //From bottom of screen
    const int kP2StatusXPosition = 200; //From right of screen
    const int kP2StatusYPosition = 20; //From bottom of screen

    const string kDefaultTankFilename = "data/tank.txt";
    const string kStartupSoundFilename = "data/sounds/startup.mp3";
    const string kMazeEdgesFilename = "data/mazes/maze";
    const string kMazePositionsFilename = "data/mazes/maze";
    const string kMazeEdgesFilenameSuffix = "Edges.txt";
    const string kMazePositionsFilenameSuffix = "StartingPositions.txt";
    const int kNumMazes = 4;

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
    const int kReset = 'R';
    const int kPause = 'P';

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
    vector<Powerup *> powerups_;
    Maze *maze_;

    void setupTanks();

    void setupMaze();

    void updateTanks();

    void drawRound(); //Draws tanks, maze, etc.

    void reset();

    void removePowerups(); //To remove the powerups that have been used

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
