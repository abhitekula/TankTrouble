#include "maze.h"

Maze::Maze(string edge_file, string positions_file, b2World *world) {
  createMaze(edge_file, world);
  loadStartingPositions(positions_file);
}

Maze::~Maze() {
  for(auto edge : maze_edges_) {
    edge->destroy();
  }
}

void Maze::createMaze(string file, b2World *world) {
  vector<ofVec2f> points;
  float x;
  float y;
  string input;

  ifstream inputFile;
  inputFile.open(file);

  if (inputFile.is_open()) {
    while (!inputFile.eof()) {
      inputFile >> input;

      if (input == kEdgeDelimiter) {
        maze_edges_.push_back(createEdge(points, world));
        points.clear();
        continue;
      }

      x = stod(input);
      inputFile >> input;
      y = stod(input);
      points.push_back(ofVec2f(x, y));
    }
  }

  inputFile.close();
}

ofxBox2dEdge *Maze::createEdge(vector<ofVec2f> points, b2World *world) {
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

  edge->addVertexes(points);
  edge->body = edge_body;
  edge->body->SetType(b2_staticBody);
  edge->create(world);
  edge->body->SetUserData(edge);
  return edge;
}

void Maze::draw() {
  for (auto edge : maze_edges_) {
    edge->draw();
  }
}

void Maze::loadStartingPositions(string file) {
  p1_starting_positions_.clear();
  p2_starting_positions_.clear();
  float x1, y1, x2, y2;

  ifstream inputFile;
  inputFile.open(file);

  if (inputFile.is_open()) {
    while (!inputFile.eof()) {
      inputFile >> x1;
      inputFile >> y1;
      inputFile >> x2;
      inputFile >> y2;
      p1_starting_positions_.push_back(ofPoint(x1, y1));
      p2_starting_positions_.push_back(ofPoint(x2, y2));
    }
  }

  inputFile.close();
}

ofVec2f Maze::getStartingPosition(bool player_one) {
  if (player_one) {
    return p1_starting_positions_[rand() % p1_starting_positions_.size()];
  } else {
    return p2_starting_positions_[rand() % p2_starting_positions_.size()];
  }
}