#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);

    // Box2d
    box2d.init();
    box2d.setGravity(0, 0);
    box2d.createGround();
    box2d.setFPS(30.0);

    b2BodyDef tank_body_def;
    tank_body_def.type = b2_dynamicBody;
    tank_body_def.position.Set(100, 100);
    tank_body_def.angle = 0;

    b2BodyDef tank_body_def_two;
    tank_body_def_two.type = b2_dynamicBody;
    tank_body_def_two.position.Set(100, 100);
    tank_body_def_two.angle = 0;

    b2Body *tank_body = box2d.getWorld()->CreateBody(&tank_body_def);
    b2Body *tank_body_two = box2d.getWorld()->CreateBody(&tank_body_def_two);

    //TODO Switch to tank polygon
    b2PolygonShape rectangle;
    rectangle.SetAsBox(20, 20);

    b2FixtureDef tank_fixture;
    tank_fixture.shape = &rectangle;
    tank_fixture.density = 1;

    tank_body->CreateFixture(&tank_fixture);
    tank_body_two->CreateFixture(&tank_fixture);

    vector <ofPoint> tank_pts = loadPoints("tank.txt");
    tank = new ofxBox2dPolygon();
    tank->addVertices(tank_pts);
    tank->setPhysics(1.0, 0.3, 0.3);
    tank->triangulatePoly();
    tank->body = tank_body;
    tank->create(box2d.getWorld());

    vector <ofPoint> tank_two_pts = loadPoints("tank2.txt");
    tank_two = new ofxBox2dPolygon();
    tank_two->addVertices(tank_two_pts);
    tank_two->setPhysics(1.0, 0.3, 0.3);
    tank_two->triangulatePoly();
    tank_two->body = tank_body_two;
    tank_two->create(box2d.getWorld());
}

vector <ofPoint> ofApp::loadPoints(string file) {
    vector <ofPoint> pts;
    vector <string> ptsStr = ofSplitString(ofBufferFromFile(file).getText(),
                                           ",");
    for (int i = 0; i < ptsStr.size(); i += 2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i + 1]);
        pts.push_back(ofPoint(x, y));
    }
    return pts;
}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
    double angle = (tank->body->GetAngle());

    if (isKeyPressed['W']) {
        tank->body->SetLinearVelocity(b2Vec2(sin(angle) * kLinearVelocity,
                                             -cos(angle) * kLinearVelocity));
    }

    if (isKeyPressed['S']) {
        tank->body->SetLinearVelocity(b2Vec2(-sin(angle) * kLinearVelocity,
                                             cos(angle) * kLinearVelocity));
    }

    if (isKeyPressed['A']) {
        tank->body->SetAngularVelocity(-kAngularVelocity);
    }

    if (isKeyPressed['D']) {
        tank->body->SetAngularVelocity(kAngularVelocity);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetHexColor(0x444342);
    ofFill();

    tank->draw();
    tank_two->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    int upper_key = toupper(key); // Standardize on upper case
    double angle = (tank->body->GetAngle());
    std::cout << "Angle: " << angle << '\n';

    if (upper_key == 'W') {
        isKeyPressed[upper_key] = true;
        tank->body->SetLinearVelocity(b2Vec2(sin(angle) * kLinearVelocity,
                                             -cos(angle) * kLinearVelocity));
    } else if (upper_key == 'S') {
        isKeyPressed[upper_key] = true;
        tank->body->SetLinearVelocity(b2Vec2(-sin(angle) * kLinearVelocity,
                                             cos(angle) * kLinearVelocity));
    } else if (upper_key == 'A') {
        isKeyPressed[upper_key] = true;
        tank->body->SetAngularVelocity(-kAngularVelocity);
    } else if (upper_key == 'D') {
        isKeyPressed[upper_key] = true;
        tank->body->SetAngularVelocity(kAngularVelocity);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    int upper_key = toupper(key); // Standardize on upper case

    if (upper_key == 'W') {
        isKeyPressed[upper_key] = false;
        tank->body->SetLinearVelocity(b2Vec2(0, 0));
    } else if (upper_key == 'S') {
        isKeyPressed[upper_key] = false;
        tank->body->SetLinearVelocity(b2Vec2(0, 0));
    } else if (upper_key == 'A') {
        isKeyPressed[upper_key] = false;
        tank->body->SetAngularVelocity(0);
    } else if (upper_key == 'D') {
        isKeyPressed[upper_key] = false;
        tank->body->SetAngularVelocity(0);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
