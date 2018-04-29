#include "maze.h"

Maze::Maze(int id, string file, b2World *world) {
  id_ = id;
  health_ = kStartingHealth;
  ammo_ = kStartingAmmo;

  createMaze(file, world);
  body->SetUserData(this);
}

void *Maze::createMaze(string file, b2World *world) {
  b2BodyDef maze_body_def;
  maze_body_def.type = b2_dynamicBody;
  b2Body *maze_body = world->CreateBody(&maze_body_def);

  b2PolygonShape rectangle;
  rectangle.SetAsBox(0, 0, b2Vec2(0, 0), 0);

  b2FixtureDef maze_fixture;
  maze_fixture.shape = &rectangle;
  maze_fixture.density = 1;

  maze_body->CreateFixture(&maze_fixture);

  vector<ofPoint> maze_pts = loadPoints(file);
  addVertices(maze_pts);
  setPhysics(0.7, 0.5, 0.5);
  triangulatePoly();
  body = maze_body;
  body->SetType(b2_staticBody);
  create(world);
}

vector<ofVec2f> Maze::loadPoints(string file) {
  vector<ofVec2f> points;
  float x;
  float y;

  ifstream inputFile;
  inputFile.open(file);

  if (inputFile.is_open()) {
    while (!inputFile.eof()) {
      inputFile >> x;
      inputFile >> y;
      points.push_back(ofVec2f(x, y));
    }
  }

  inputFile.close();
  return points;
}

void Maze::draw() {
  super::draw();
  for (auto bullet : bullets_) {
    bullet->draw();
  }
}