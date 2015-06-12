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
    
    // main elements
    vector<Level> levels;
    vector<Wave> waves;
    
    // methods
    void update();
    void draw();
    void tap(float x, float y);
    void gotoNextLevel();
    
    // various
    bool active;
    ofTrueTypeFont *fonts;
    
    // flash
    int overlayOpacity;
    int realOpacity;
    
    // transition
    float transitionPos;
    float transitionEnd;
    int nextLevel, currentLevel;
    bool isInfoScreen, gotoNext;

private:
    void killWave(int i);
};