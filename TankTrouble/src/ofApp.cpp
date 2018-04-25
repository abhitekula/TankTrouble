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
  box2d.createBounds();
  box2d.setFPS(30.0);

  // Setup Collision Detecter
  CollisionDetector *detector = new CollisionDetector();
  box2d.getWorld()->SetContactListener(detector);

  // Create Tanks
  this->setupTanks();
}

void ofApp::setupTanks() {
  p1_tank = new Tank(1, kDefaultTankFilename, box2d.getWorld());
  p2_tank = new Tank(2, kDefaultTankFilename, box2d.getWorld());

  p1_tank->body->SetLinearDamping(kDamping);
  p1_tank->body->SetAngularDamping(kDamping);
  p1_tank->body->SetBullet(true);
  p1_tank->setPosition(200, 250);
  p1_tank->setRotation(90);

  p2_tank->body->SetLinearDamping(kDamping);
  p2_tank->body->SetAngularDamping(kDamping);
  p2_tank->setPosition(600, 250);
  p2_tank->setRotation(-90);
}

//--------------------------------------------------------------
void ofApp::update() {
  box2d.update();

  if (isKeyPressed[kP1Forward]) {
    double angle = (p1_tank->body->GetAngle());
    p1_tank->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP1Backward]) {
    double angle = (p1_tank->body->GetAngle());
    p1_tank->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP1Left]) {
    p1_tank->body->SetAngularVelocity(-kAngularVelocity);
  }

  if (isKeyPressed[kP1Right]) {
    p1_tank->body->SetAngularVelocity(kAngularVelocity);
  }

  if (isKeyPressed[kP2Forward]) {
    double angle = (p2_tank->body->GetAngle());
    p2_tank->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP2Backward]) {
    double angle = (p2_tank->body->GetAngle());
    p2_tank->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  }

  if (isKeyPressed[kP2Left]) {
    p2_tank->body->SetAngularVelocity(-kAngularVelocity);
  }

  if (isKeyPressed[kP2Right]) {
    p2_tank->body->SetAngularVelocity(kAngularVelocity);
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  box2d.draw();

  ofSetHexColor(0xFF0000);
  ofFill();
  p1_tank->draw();

  ofSetHexColor(0x0000FF);
  ofFill();
  p2_tank->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  int upper_key = toupper(key); // Standardize on upper case

  if (upper_key == kP1Forward) {
    double angle = (p1_tank->body->GetAngle());
    p1_tank->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  } else if (upper_key == kP1Backward) {
    double angle = (p1_tank->body->GetAngle());
    p1_tank->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  } else if (upper_key == kP1Left) {
    p1_tank->body->SetAngularVelocity(-kAngularVelocity);
  } else if (upper_key == kP1Right) {
    p1_tank->body->SetAngularVelocity(kAngularVelocity);
  } else if (upper_key == kP2Forward) {
    double angle = (p2_tank->body->GetAngle());
    p2_tank->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  } else if (upper_key == kP2Backward) {
    double angle = (p2_tank->body->GetAngle());
    p2_tank->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  } else if (upper_key == kP2Left) {
    p2_tank->body->SetAngularVelocity(-kAngularVelocity);
  } else if (upper_key == kP2Right) {
    p2_tank->body->SetAngularVelocity(kAngularVelocity);
  } else if (upper_key == kP1Shoot) {
    p1_tank->shoot(box2d.getWorld());
    return;
  } else if (upper_key == kP2Shoot) {
    p2_tank->shoot(box2d.getWorld());
    return;
  } else {
    return;
  }

  isKeyPressed[upper_key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  int upper_key = toupper(key); // Standardize on upper case

  if (upper_key == kP1Forward) {
    p1_tank->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP1Backward) {
    p1_tank->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP1Left) {
    p1_tank->body->SetAngularVelocity(0);
  } else if (upper_key == kP1Right) {
    p1_tank->body->SetAngularVelocity(0);
  } else if (upper_key == kP2Forward) {
    p2_tank->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP2Backward) {
    p2_tank->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP2Left) {
    p2_tank->body->SetAngularVelocity(0);
  } else if (upper_key == kP2Right) {
    p2_tank->body->SetAngularVelocity(0);
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
void ofApp::windowResized(int w, int h) { box2d.createBounds(); }

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
