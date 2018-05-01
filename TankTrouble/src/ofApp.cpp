#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(kFPS);
  ofBackgroundHex(0xfdefc2);
  ofSetLogLevel(OF_LOG_NOTICE);
  ofSetVerticalSync(true);
  is_round_over_ = false;

  // Box2d
  box2d_.init();
  box2d_.setGravity(0, 0);
  box2d_.createBounds();
  box2d_.setFPS(kFPS);

  // Setup Collision Detecters
  CollisionDetector *collision_detector = new CollisionDetector();
  box2d_.getWorld()->SetContactListener(collision_detector);

  // Setup Maze
  setupMazes();

  // Create Tanks
  setupTanks();

  // Startup Sound
  startup_sound_player_ = new ofSoundPlayer();
  startup_sound_player_->setMultiPlay(true);
  startup_sound_player_->load(kStartupSoundFilename);
  startup_sound_player_->play();
}

void ofApp::setupMazes() {
  for (int i = 1; i <= kNumMazes; i++) {
    Maze *maze =
        new Maze((kMazeEdgesFilename + to_string(i) + "Edges.txt"),
                 (kMazePositionsFilename + to_string(i) + "StartingPositions.txt"),
                 box2d_.getWorld());
    mazes_.push_back(maze);
  }
  current_maze_ = mazes_[rand() % mazes_.size()];
}

void ofApp::setupTanks() {
  p1_tank_ = new Tank(1, kDefaultTankFilename, box2d_.getWorld());
  p2_tank_ = new Tank(2, kDefaultTankFilename, box2d_.getWorld());

  p1_tank_->body->SetLinearDamping(kDamping);
  p1_tank_->body->SetAngularDamping(kDamping);
  p1_tank_->body->SetBullet(true);
  p1_tank_->setPosition(current_maze_->getStartingPosition(true));
  p1_tank_->setRotation(0);

  p2_tank_->body->SetLinearDamping(kDamping);
  p2_tank_->body->SetAngularDamping(kDamping);
  p2_tank_->body->SetBullet(true);
  p2_tank_->setPosition(current_maze_->getStartingPosition(false));
  p2_tank_->setRotation(0);
}

//--------------------------------------------------------------
void ofApp::update() {
  // Check if tanks are dead
  if (p1_tank_->isDead() && !is_round_over_) {
    cout << "P1 is Dead" << endl;
    p2_score_++;
    is_round_over_ = true;
  } else if (p2_tank_->isDead() && !is_round_over_) {
    cout << "P2 is Dead" << endl;
    p1_score_++;
    is_round_over_ = true;
  } else if (!paused_) {
    box2d_.update();
    updateTanks();
  }
}

void ofApp::updateTanks() {
  if (is_key_pressed_[kP1Forward]) {
    double angle = (p1_tank_->body->GetAngle());
    p1_tank_->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  }

  if (is_key_pressed_[kP1Backward]) {
    double angle = (p1_tank_->body->GetAngle());
    p1_tank_->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  }

  if (is_key_pressed_[kP1Left]) {
    p1_tank_->body->SetAngularVelocity(-kAngularVelocity);
  }

  if (is_key_pressed_[kP1Right]) {
    p1_tank_->body->SetAngularVelocity(kAngularVelocity);
  }

  if (is_key_pressed_[kP2Forward]) {
    double angle = (p2_tank_->body->GetAngle());
    p2_tank_->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  }

  if (is_key_pressed_[kP2Backward]) {
    double angle = (p2_tank_->body->GetAngle());
    p2_tank_->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  }

  if (is_key_pressed_[kP2Left]) {
    p2_tank_->body->SetAngularVelocity(-kAngularVelocity);
  }

  if (is_key_pressed_[kP2Right]) {
    p2_tank_->body->SetAngularVelocity(kAngularVelocity);
  }
}

void ofApp::reset() {
  p1_tank_->reset();
  p2_tank_->reset();

  is_round_over_ = false;

  p1_tank_->setPosition(current_maze_->getStartingPosition(true));
  p1_tank_->setRotation(0);
  p2_tank_->setPosition(current_maze_->getStartingPosition(false));
  p2_tank_->setRotation(0);
}

//--------------------------------------------------------------
void ofApp::draw() {
  box2d_.draw();

  string score = "Score: Player 1 - " + ofToString(p1_score_) + " Player 2 - " +
                 ofToString(p2_score_);
  string fps = "FPS: " + ofToString(ofGetFrameRate());
  ofSetHexColor(000000);
  ofDrawBitmapString(score, 0, 20);
  ofDrawBitmapString(fps, ofGetWidth() - 100, 20);

  if (!is_round_over_) {
    current_maze_->draw();

    ofSetHexColor(0xFF0000);
    ofFill();
    p1_tank_->draw();

    ofSetHexColor(0x0000FF);
    ofFill();
    p2_tank_->draw();
  } else {
    string end_message = "Press 'R' to start the next round:";
    ofSetHexColor(000000);
    ofDrawBitmapString(end_message, ofGetWidth() / 2, ofGetHeight() / 2);
    reset();
    is_round_over_ = true;
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  int upper_key = toupper(key); // Standardize on upper case

  if (upper_key == kP1Forward) {
    double angle = (p1_tank_->body->GetAngle());
    p1_tank_->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  } else if (upper_key == kP1Backward) {
    double angle = (p1_tank_->body->GetAngle());
    p1_tank_->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  } else if (upper_key == kP1Left) {
    p1_tank_->body->SetAngularVelocity(-kAngularVelocity);
  } else if (upper_key == kP1Right) {
    p1_tank_->body->SetAngularVelocity(kAngularVelocity);
  } else if (upper_key == kP2Forward) {
    double angle = (p2_tank_->body->GetAngle());
    p2_tank_->body->SetLinearVelocity(
        b2Vec2(sin(angle) * kLinearVelocity, -cos(angle) * kLinearVelocity));
  } else if (upper_key == kP2Backward) {
    double angle = (p2_tank_->body->GetAngle());
    p2_tank_->body->SetLinearVelocity(
        b2Vec2(-sin(angle) * kLinearVelocity, cos(angle) * kLinearVelocity));
  } else if (upper_key == kP2Left) {
    p2_tank_->body->SetAngularVelocity(-kAngularVelocity);
  } else if (upper_key == kP2Right) {
    p2_tank_->body->SetAngularVelocity(kAngularVelocity);
  } else if (upper_key == kP1Shoot && !paused_) {
    p1_tank_->shoot(box2d_.getWorld());
    return;
  } else if (upper_key == kP2Shoot && !paused_) {
    p2_tank_->shoot(box2d_.getWorld());
    return;
  } else if (is_round_over_ && upper_key == 'R') {
    reset();
    return;
  } else if (upper_key == 'P') {
    paused_ ? paused_ = false : paused_ = true;
    return;
  } else {
    return;
  }

  is_key_pressed_[upper_key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  int upper_key = toupper(key); // Standardize on upper case

  if (upper_key == kP1Forward) {
    p1_tank_->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP1Backward) {
    p1_tank_->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP1Left) {
    p1_tank_->body->SetAngularVelocity(0);
  } else if (upper_key == kP1Right) {
    p1_tank_->body->SetAngularVelocity(0);
  } else if (upper_key == kP2Forward) {
    p2_tank_->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP2Backward) {
    p2_tank_->body->SetLinearVelocity(b2Vec2(0, 0));
  } else if (upper_key == kP2Left) {
    p2_tank_->body->SetAngularVelocity(0);
  } else if (upper_key == kP2Right) {
    p2_tank_->body->SetAngularVelocity(0);
  } else {
    return;
  }

  is_key_pressed_[upper_key] = false;
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
void ofApp::windowResized(int w, int h) { box2d_.createBounds(); }

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
