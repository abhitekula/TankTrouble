#include "maze.h"

Maze::Maze(string file, b2World *world) {
  createMaze(file, world);
}

void *Maze::createMaze(string file, b2World *world) {
  ofxBox2dEdge *edge = new ofxBox2dEdge();
  b2BodyDef edge_body_def;
  edge_body_def.type = b2_staticBody;
  b2Body *edge_body = world->CreateBody(&edge_body_def);

  b2PolygonShape rectangle;
  rectangle.SetAsBox(0, 0, b2Vec2(0, 0), 0);

  b2FixtureDef edge_fixture;
  edge_fixture.shape = &rectangle;
  edge_fixture.density = 1;

  edge_body->CreateFixture(&edge_fixture);

  vector<ofVec2f> edge_pts = loadPoints(file);
  edge->addVertexes(edge_pts);
  edge->body = edge_body;
  edge->body->SetType(b2_staticBody);
  edge->create(world);
  edge->body->SetUserData(edge);

  maze_edges_.push_back(edge);
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
  for (auto edge : maze_edges_) {
    edge->draw();
  }
}