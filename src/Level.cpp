#include "Level.h"

Level::Level(string _name){
    cout << "creating level: " << _name << endl;
    name = _name;
    bigFont.loadFont("AvenirNext-UltraLight.ttf", 100);
    smallFont.loadFont("AvenirNext-UltraLight.ttf", 40);
    targetCount = 0;
    specialLevel = -1; // false by default
    reset();
}

void Level::reset(){
    completed = false;
    intro = false;
    transitionAnimation = ofGetWidth()/1.5;
    for (int i=0; i<points.size(); i++) points[i]->reset();
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
    
    for (int i=0; i<points.size(); i++) if(points[i]->kind == TARGET_OBSTACLE && points[i]->hasCollided) validCount++;
    if(validCount==targetCount) completed = true;
}

void Level::draw(float opacity){
    for (int i=0; i<points.size(); i++) points[i]->draw(opacity);
    if(specialLevel == 0){              // start level
        ofSetColor(255, 255, 255, 255*opacity);
        ofRectangle bounds = smallFont.getStringBoundingBox(restartText, 0, 0);
        smallFont.drawString(beginText, (ofGetWidth()-bounds.width)/2, (ofGetHeight()-bounds.height)/2+70);
    }
    else if(specialLevel==1){           // you won level
        ofSetColor(255, 255, 255, 255*opacity);
        
        ofRectangle bounds = bigFont.getStringBoundingBox(wonText, 0, 0);
        bigFont.drawString(wonText, (ofGetWidth()-bounds.width)/2 , (ofGetHeight()-bounds.height)/2);
        
        bounds = smallFont.getStringBoundingBox(restartText, 0, 0);
        smallFont.drawString(restartText, (ofGetWidth()-bounds.width)/2, (ofGetHeight()-bounds.height)/2+70);
    }
}