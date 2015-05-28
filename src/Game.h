#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Level.h"
#include "Wave.h"
#include "Obstacle.h"
#include "ofxXmlSettings.h"

class Game{
public:
    Game();
    void init();
    vector<Level> levels;
    vector<Wave> waves;
    vector<Obstacle *> obstacles;
    
    void update();
    void draw();
    void tap(float x, float y);
    
    ofxXmlSettings XML;
    float transitionTimer;
private:
    int currentLevel;
};