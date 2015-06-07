#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Level.h"
#include "Wave.h"
#include "ofxXmlSettings.h"

class Game{
public:
    Game();
    void init();
    vector<Level> levels;
    vector<Wave> waves;
    
    void update();
    void draw();
    void tap(float x, float y);
    
    ofxXmlSettings XML;
    float transitionTimer;
    bool active;
private:
    int currentLevel;
};