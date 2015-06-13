#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "Utils.h"
#include "PointElement.h"
#include "LineElement.h"
#include "Title.h"
#include "Link.h"

class Level{
public:
    Level(string name, string _minWaveCount, ofTrueTypeFont *_fonts, ofColor bg);
    void reset();
    
    void update();
    void draw(float opacity);
    void draw(float opacity, bool background);
    
    void addPoint(string x, string y, string kind);
    void addLine(string x1, string y1, string x2, string y2);
    void addTitle(string text, string x, string y, string font);
    void addButton(string x, string y, string kind, string text);
    void addChain();
    void linkToLastChain(string x, string y);
    string name;
    
    // game elements
    vector<PointElement *> points;
    vector<LineElement *> lines;
    vector<Title *> titles;
    vector<Link *> chains;
    
    bool completed, intro;
    float transitionAnimation;
    int targetCount;
    
    string wonText = "YOU WON !!!";
    string restartText = "restart";
    string beginText = "Start";
    
    string minWaveCount;
    int waveCount;
    ofColor bg;

private:
    ofTrueTypeFont *fonts;
//    ofImage *bg;
//    ofTrueTypeFont bigFont;
//    ofTrueTypeFont smallFont;
};