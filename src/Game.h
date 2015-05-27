#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Level.h"
#include "Wave.h"
#include "Obstacle.h"
#include "ofxXmlSettings.h"
#include "ofxMask.h"

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
    ofxMask mask;
    ofImage testImage;
    
private:
    int currentLevel;
    ofTrueTypeFont font;
};