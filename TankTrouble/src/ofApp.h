#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp {

    //Constants
    const double kLinearVelocity = 5;
    const double kAngularVelocity = 2;

private:
    bool isKeyPressed[255];
    ofxBox2d box2d;
    ofxBox2dPolygon *tank;
    ofxBox2dPolygon *tank_two;

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
