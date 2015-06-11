#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "Utils.h"
#include "PointElement.h"
#include "LineElement.h"
#include "Title.h"

class Level{
public:
    Level(string name, string _minWaveCount, ofTrueTypeFont *_fonts);
    void reset();
    
    void update();
    void draw(float opacity);
    
    void addPoint(string x, string y, string kind);
    void addLine(string x1, string y1, string x2, string y2);
    void addTitle(string text, string x, string y, string font);
    void addButton(string x, string y, string kind, string text);
    string name;
    
    vector<PointElement *> points;
    vector<LineElement *> lines;
    vector<Title *> titles;

    bool completed, intro;
    float transitionAnimation;
    
    string wonText = "YOU WON !!!";
    string restartText = "restart";
    string beginText = "Start";
    
    string minWaveCount;
    int waveCount;

private:
    int targetCount;
    ofTrueTypeFont *fonts;
    ofImage *bg;
//    ofTrueTypeFont bigFont;
//    ofTrueTypeFont smallFont;
};