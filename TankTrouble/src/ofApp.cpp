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
  setupMaze();

  // Create Tanks
  setupTanks();

  // Startup Sound
  startup_sound_player_ = new ofSoundPlayer();
  startup_sound_player_->setMultiPlay(true);
  startup_sound_player_->load(kStartupSoundFilename);
  startup_sound_player_->play();
}

void ofApp::setupMaze() {
  if (maze_) {
    delete maze_;
  }

  int index = rand() % kNumMazes + 1;
  maze_ = new Maze(
      (kMazeEdgesFilename + to_string(index) + "Edges.txt"),
      (kMazePositionsFilename + to_string(index) + "StartingPositions.txt"),
      box2d_.getWorld());
}

void ofApp::setupTanks() {
  p1_tank_ = new Tank(kDefaultTankFilename, box2d_.getWorld());
  p2_tank_ = new Tank(kDefaultTankFilename, box2d_.getWorld());

  p1_tank_->setPosition(maze_->getStartingPosition(true));
  p2_tank_->setPosition(maze_->getStartingPosition(false));
}

//--------------------------------------------------------------
void ofApp::update() {
  // Check if tanks are dead
  if (p1_tank_->isDead() && !is_round_over_) {
    cout << "P1 is Dead" << endl;
    p2_score_++;
    is_round_over_ = true;
    //Play tank dead sound
  } else if (p2_tank_->isDead() && !is_round_over_) {
    cout << "P2 is Dead" << endl;
    p1_score_++;
    is_round_over_ = true;
  } else if (!paused_) {
    box2d_.update();
    updateTanks();
    removePowerups();

    // Randomly add powerups
    if (rand() % 1000 < kPowerupChance) {
      powerups_.push_back(new Powerup(box2d_.getWorld()));
    }
  }
}

void ofApp::updateTanks() {
  double p1_linear_velocity = p1_tank_->getLinearVelocity();
  double p2_linear_velocity = p2_tank_->getLinearVelocity();
  double p1_angular_velocity = p1_tank_->getAngularVelocity();
  double p2_angular_velocity = p2_tank_->getAngularVelocity();

  if (is_key_pressed_[kP1Forward]) {
    double angle = (p1_tank_->body->GetAngle());
    p1_tank_->body->SetLinearVelocity(b2Vec2(sin(angle) * p1_linear_velocity,
                                             -cos(angle) * p1_linear_velocity));
  }

  if (is_key_pressed_[kP1Backward]) {
    double angle = (p1_tank_->body->GetAngle());
    p1_tank_->body->SetLinearVelocity(b2Vec2(-sin(angle) * p1_linear_velocity,
                                             cos(angle) * p1_linear_velocity));
  }

  if (is_key_pressed_[kP1Left]) {
    p1_tank_->body->SetAngularVelocity(-p1_angular_velocity);
  }

  if (is_key_pressed_[kP1Right]) {
    p1_tank_->body->SetAngularVelocity(p1_angular_velocity);
  }

  if (is_key_pressed_[kP2Forward]) {
    double angle = (p2_tank_->body->GetAngle());
    p2_tank_->body->SetLinearVelocity(b2Vec2(sin(angle) * p2_linear_velocity,
                                             -cos(angle) * p2_linear_velocity));
  }

  if (is_key_pressed_[kP2Backward]) {
    double angle = (p2_tank_->body->GetAngle());
    p2_tank_->body->SetLinearVelocity(b2Vec2(-sin(angle) * p2_linear_velocity,
                                             cos(angle) * p2_linear_velocity));
  }

  if (is_key_pressed_[kP2Left]) {
    p2_tank_->body->SetAngularVelocity(-p2_angular_velocity);
  }

  if (is_key_pressed_[kP2Right]) {
    p2_tank_->body->SetAngularVelocity(p2_angular_velocity);
  }
}

void ofApp::removePowerups() {
  vector<int> indexes_to_remove;
  for (int i = 0; i < powerups_.size(); i++) {
    if (!powerups_[i]->body->GetUserData()) {
      indexes_to_remove.push_back(i);
    }
  }

  for (auto i : indexes_to_remove) {
    powerups_[i]->destroy();
    powerups_.erase(powerups_.begin() + i);
  }
}

void ofApp::reset() {
  p1_tank_->reset();
  p2_tank_->reset();

  for (auto powerup : powerups_) {
    powerup->destroy();
  }
  powerups_.clear();

  is_round_over_ = false;

  p1_tank_->setPosition(maze_->getStartingPosition(true));
  p1_tank_->setRotation(0);
  p2_tank_->setPosition(maze_->getStartingPosition(false));
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
    maze_->draw();

    ofSetHexColor(0xFF0000);
    ofFill();
    p1_tank_->draw();

    ofSetHexColor(0x0000FF);
    ofFill();
    p2_tank_->draw();

    for (auto powerup : powerups_) {
      ofSetHexColor(powerup->getColor());
      ofFill();
      powerup->draw();
    }

    ofSetHexColor(000000);
    string p1_status = "P1 Ammo: " + ofToString(p1_tank_->getAmmo()) +
                       " Health: " + ofToString(p1_tank_->getHealth());
    string p2_status = "P2 Ammo: " + ofToString(p2_tank_->getAmmo()) +
                       " Health: " + ofToString(p2_tank_->getHealth());
    ofDrawBitmapString(p1_status, 50, ofGetHeight() - 20);
    ofDrawBitmapString(p2_status, ofGetWidth() - 200, ofGetHeight() - 20);

    if (paused_) {
      string pause_message = "Press 'P' to unpause:";
      ofDrawBitmapString(pause_message, ofGetWidth() / 2, ofGetHeight() / 2);
    }
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

  if (upper_key == kP1Shoot && !is_round_over_ && !paused_) {
    p1_tank_->shoot(box2d_.getWorld());
  } else if (upper_key == kP2Shoot && !is_round_over_ && !paused_) {
    p2_tank_->shoot(box2d_.getWorld());
  } else if (is_round_over_ && upper_key == 'R') {
    setupMaze();
    reset();
  } else if (!is_round_over_ && upper_key == 'P') {
    paused_ ? paused_ = false : paused_ = true;
  } else {
    is_key_pressed_[upper_key] = true;
  }
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
void ofApp::windowResized(int w, int h) {
  // box2d_.createBounds();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
