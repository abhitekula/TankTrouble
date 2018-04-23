#include "tank.h"

Tank::Tank(string file, b2World *world) {
    createTank(file, world);
}

void *Tank::createTank(string file, b2World *world) {
  b2BodyDef tank_body_def;
  tank_body_def.type = b2_dynamicBody;
  b2Body *tank_body = world->CreateBody(&tank_body_def);

  b2PolygonShape rectangle;
  rectangle.SetAsBox(0, 0, b2Vec2(0, 0), 0);

  b2FixtureDef tank_fixture;
  tank_fixture.shape = &rectangle;
  tank_fixture.density = 1;

  tank_body->CreateFixture(&tank_fixture);

  vector<ofPoint> tank_pts = loadPoints(file);
  addVertices(tank_pts);
  setPhysics(0.7, 0.5, 0.5);
  triangulatePoly();
  body = tank_body;
  body->SetType(b2_dynamicBody);
  create(world);
}

vector<ofPoint> Tank::loadPoints(string file) {
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