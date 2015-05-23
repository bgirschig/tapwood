#pragma once

#include "ofMain.h"
#include "ofxiOS.h"

#include "ofxXmlSettings.h"
#include "Level.h"

#include "Wave.h"
#include "Obstacle.h"

class GameHandler {
public:
    
    // constructors
    GameHandler();
    void init();
    
    // levels
    ofxXmlSettings XML;
    vector<Level> levels;
    
    // game elements
    vector<Wave> waves;
    vector<Obstacle *> obstacles;
    
    // methods
    void update();
    void draw();
    void onTap(float x, float y);
};