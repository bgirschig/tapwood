#include "Level.h"

Level::Level(string _name){
    cout << "creating level: " << _name << endl;
    name = _name;
    completed = false;
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
    
}