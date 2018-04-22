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

  tank = createTank("data/tank.txt");
  tank_two = createTank("data/tank2.txt");
}

ofxBox2dPolygon *ofApp::createTank(string file) {
  ofxBox2dPolygon *tank = new ofxBox2dPolygon();

  b2BodyDef tank_body_def;
  tank_body_def.type = b2_dynamicBody;
  tank_body_def.position.Set(100, 100);
  tank_body_def.angle = 0;

  b2Body *tank_body = box2d.getWorld()->CreateBody(&tank_body_def);

  b2PolygonShape rectangle;
  rectangle.SetAsBox(20, 20);

  b2FixtureDef tank_fixture;
  tank_fixture.shape = &rectangle;
  tank_fixture.density = 1;

  tank_body->CreateFixture(&tank_fixture);

  vector<ofPoint> tank_pts = loadPoints(file);
  tank->addVertices(tank_pts);
  tank->setPhysics(0.5, 0.5, 0.5);
  tank->triangulatePoly();
  tank->body = tank_body;
  tank->create(box2d.getWorld());

  return tank;
}

vector<ofPoint> ofApp::loadPoints(string file) {
  vector<ofPoint> points;
  float x;
  float y;

  ifstream inputFile;
  inputFile.open(file);

  if (inputFile.is_open()) {
    while (!inputFile.eof()) {
      inputFile >> x;
      inputFile >> y;
      points.push_back(ofPoint(x, y));
    }
  }

  inputFile.close();
  return points;
}

//--------------------------------------------------------------
void ofApp::update() {
  box2d.update();

  if (isKeyPressed[kP1Forward]) {
    double angle = (tank->body->GetAngle());
    tank->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP1Backward]) {
    double angle = (tank->body->GetAngle());
    tank->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP1Left]) {
    tank->body->SetAngularVelocity(-kAngularVelocity);
  }

  if (isKeyPressed[kP1Right]) {
    tank->body->SetAngularVelocity(kAngularVelocity);
  }

  if (isKeyPressed[kP2Forward]) {
    double angle = (tank_two->body->GetAngle());
    tank_two->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP2Backward]) {
    double angle = (tank_two->body->GetAngle());
    tank_two->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP2Left]) {
    tank_two->body->SetAngularVelocity(-kAngularVelocity);
  }

  if (isKeyPressed[kP2Right]) {
    tank_two->body->SetAngularVelocity(kAngularVelocity);
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofSetHexColor(0xFF0000);
  ofFill();
  tank->draw();

  ofSetHexColor(0x0000FF);
  ofFill();
  tank_two->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  int upper_key = toupper(key); // Standardize on upper case

  if (upper_key == kP1Forward) {
    double angle = (tank->body->GetAngle());
    tank->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  } else if (upper_key == kP1Backward) {
    double angle = (tank->body->GetAngle());
    tank->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  } else if (upper_key == kP1Left) {
    tank->body->SetAngularVelocity(-kAngularVelocity);
  } else if (upper_key == kP1Right) {
    tank->body->SetAngularVelocity(kAngularVelocity);
  } else if (upper_key == kP2Forward) {
    double angle = (tank_two->body->GetAngle());
    tank_two->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  } else if (upper_key == kP2Backward) {
    double angle = (tank_two->body->GetAngle());
    tank_two->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  } else if (upper_key == kP2Left) {
    tank_two->body->SetAngularVelocity(-kAngularVelocity);
  } else if (upper_key == kP2Right) {
    tank_two->body->SetAngularVelocity(kAngularVelocity);
  } else {
    return;
  }

  isKeyPressed[upper_key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  int upper_key = toupper(key); // Standardize on upper case

  if (upper_key == kP1Forward) {
    tank->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP1Backward) {
    tank->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP1Left) {
    tank->body->SetAngularVelocity(0);
  } else if (upper_key == kP1Right) {
    tank->body->SetAngularVelocity(0);
  } else if (upper_key == kP2Forward) {
    tank_two->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP2Backward) {
    tank_two->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP2Left) {
    tank_two->body->SetAngularVelocity(0);
  } else if (upper_key == kP2Right) {
    tank_two->body->SetAngularVelocity(0);
  } else {
    return;
  }

  isKeyPressed[upper_key] = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
