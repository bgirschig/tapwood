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
    bool simulateTouch;
    ofTrueTypeFont *fonts;
    
    // flash
    int overlayOpacity;
    int realOpacity;
    static ofEvent<string> soundEvent;
    
    // transition
    float transitionPos;
    float transitionEnd_1;
    float transitionEnd_2;
    int nextLevel, currentLevel;
    bool isInfoScreen, isMenuScreen, gotoNext, restart;
    void killWave(int i);
    
    static ofEvent<string> playSoundEvent;
};