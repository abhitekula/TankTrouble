#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp {

    //Constants
    const double kLinearVelocity = 10;
    const double kAngularVelocity = 3;
    const double kDamping = 1.5;
    const int kP1Forward = 'W';
    const int kP1Backward = 'S';
    const int kP1Right = 'D';
    const int kP1Left = 'A';
    const int kP2Forward = OF_KEY_UP;
    const int kP2Backward = OF_KEY_DOWN;
    const int kP2Right = OF_KEY_RIGHT;
    const int kP2Left = OF_KEY_LEFT;

private:
    bool isKeyPressed[255];
    ofxBox2d box2d;
    ofxBox2dPolygon *tank;
    ofxBox2dPolygon *tank_two;
    ofxBox2dPolygon *wall;

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

    vector <ofPoint> loadPoints(string file);

    ofxBox2dPolygon* createTank(string file);
};
