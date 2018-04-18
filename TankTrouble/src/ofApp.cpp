#include "ofApp.h"
#include "ofxBox2dBaseShape.h"
#include "ofxBox2dPolygonUtils.h"

//--------------------------------------------------------------
void ofApp::setup(){
        ofDisableAntiAliasing();
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
        tank_body_def.position.Set(100,100);
        tank_body_def.angle = 0;

        tank_body = box2d.getWorld()->CreateBody(&tank_body_def);

        //TODO Switch to tank polygon
        b2PolygonShape rectangle;
        rectangle.SetAsBox(20,20);

        b2FixtureDef tank_fixture;
        tank_fixture.shape = &rectangle;
        tank_fixture.density = 1;
        tank_body->CreateFixture(&tank_fixture);

        tank_body->SetAngularVelocity(10);

        vector <ofPoint> pts = loadPoints("tank.dat");
        shared_ptr<ofxBox2dPolygon> poly = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
        poly->addVertices(pts);
        poly->setPhysics(1.0, 0.3, 0.3);
        poly->triangulatePoly();
        // poly.get()->body = tank_body;
        poly.get()->body = tank_body;
        poly->create(box2d.getWorld());
        polyShapes.push_back(poly);
}

vector <ofPoint> ofApp::loadPoints(string file) {
        vector <ofPoint> pts;
        vector <string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
        for (int i=0; i<ptsStr.size(); i+=2) {
                float x = ofToFloat(ptsStr[i]);
                float y = ofToFloat(ptsStr[i+1]);
                pts.push_back(ofPoint(x, y));
        }
        return pts;
}

//--------------------------------------------------------------
void ofApp::update(){
        polyShapes[0].get()->body->SetAngularVelocity( 2 );
        box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
        ofSetHexColor(0x444342);
        ofFill();

        for (int i=0; i<polyShapes.size(); i++) {
                std::cout << polyShapes[i].get()->body->GetAngularVelocity() << '\n';
                polyShapes[i]->draw();
        }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
