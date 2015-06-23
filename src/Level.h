#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "Utils.h"
#include "PointElement.h"
#include "LineElement.h"
#include "Link.h"

class Level{
public:
    Level(string name, string _minWaveCount, ofTrueTypeFont *_fonts, ofColor bg);
    void reset();
    
    void update();
    void draw(float opacity);
    void draw(float opacity, bool background);
    void drawTuto(float opacity);
    
    void addPoint(string x, string y, string kind);
    void addLine(string x1, string y1, string x2, string y2);
    void addRotLine(string x1, string y1, string x2, string y2);
    void addChain();
    void linkToLastChain(string x, string y);
    string name;
    
    // game elements
    vector<PointElement *> points;
    vector<LineElement *> lines;
    vector<Link *> chains;
    
    bool completed, intro;
    float transitionAnimation;
    int targetCount;
    
    string wonText = "YOU WON !!!";
    string restartText = "restart";
    string beginText = "Start";

    int minWaveCount;
    int remainingWaves;
    int retryTimer;
    bool failed;
    ofColor bg;
    
private:
    ofTrueTypeFont *fonts;
//    ofImage *bg;
//    ofTrueTypeFont bigFont;
//    ofTrueTypeFont smallFont;
};