#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Level.h"
#include "Wave.h"
#include "poco/string.h"

class Game{
public:
    Game();
    void init(ofTrueTypeFont *_fonts);
    vector<Level> levels;
    vector<Wave> waves;
    vector<ofImage> backgrounds;
    
    void update();
    void draw();
    void tap(float x, float y);
    
    float transitionTimer;
    bool active;
    int currentLevel;
    
    ofTrueTypeFont *fonts;
};