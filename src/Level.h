#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "PointElement.h"
#include "LineElement.h"


class Level{
public:
    Level(string name);
    void reset();
    
    void update();
    void draw(float opacity);
    
    void addPoint(float x, float y, ElementKind kind);
    void addPoint(float x, float y, string kind);
    string name;
    vector<PointElement *> points;
    vector<LineElement *> lines;

    bool completed, intro;
    float transitionAnimation;
    int specialLevel;
    
    string wonText = "YOU WON !!!";
    string restartText = "restart";
    string beginText = "Start";
    
private:
    int targetCount;
    ofTrueTypeFont bigFont;
    ofTrueTypeFont smallFont;
};