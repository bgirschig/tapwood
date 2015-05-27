#include "Level.h"

Level::Level(string _name){
    cout << "creating level: " << _name << endl;
    name = _name;
    reset();
}
void Level::reset(){
    completed = false;
    targetCount = 0;
    intro = false;
    transitionAnimation = ofGetWidth()/1.5;
}
void Level::addPoint(float x, float y, ElementKind kind){
    points.push_back(new Obstacle(ofVec2f(x,y), kind));
    if(kind==TARGET_OBSTACLE) targetCount ++;
}

void Level::addPoint(float x, float y, string kind){
    if(kind=="DESTROYER_OBSTACLE")
        addPoint(x, y, DESTROYER_OBSTACLE);
    else if(kind=="TARGET_OBSTACLE")
        addPoint(x, y, TARGET_OBSTACLE);
}
void Level::update(){
    int validCount = 0;
    for (int i=0; i<points.size(); i++) if(points[i]->valid) validCount++;
    if(validCount==targetCount) completed = true;
}
void Level::draw(){
    for (int i=0; i<points.size(); i++) points[i]->draw();
//    if(transitionAnimation>0){
//        glLineWidth(1);
//        ofFill(); ofSetColor(0,10,30);
//        ofCircle(ofGetWidth()/2, ofGetHeight()/2, transitionAnimation);
//
//        ofSetCircleResolution(200);
//        ofNoFill(); ofSetColor(255);
//        ofCircle(ofGetWidth()/2, ofGetHeight()/2, transitionAnimation);
//        ofSetCircleResolution(20);
//    }
}