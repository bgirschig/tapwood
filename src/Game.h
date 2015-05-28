#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Level.h"
#include "Wave.h"
#include "PointElement.h"
#include "ofxXmlSettings.h"

class Game{
public:
    Game();
    void init();
    vector<Level> levels;
    vector<Wave> waves;
    vector<PointElement *> elements;
    
    void update();
    void draw();
    void tap(float x, float y);
    
    ofxXmlSettings XML;
    float transitionTimer;
private:
    int currentLevel;
};