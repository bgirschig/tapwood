#pragma once

#include "ofMain.h"
#include <stdio.h>

class Calibrator{
public:
    Calibrator();
    void init();
    void update();
    void draw();
    
    ofMatrix4x4 calMatrix;
    void convert(ofVec3f & pos);
    void onCalibrationPoint();
    void setMatrix(string matrix);
    
    bool done;
    bool next;
    int step;
    
    ofColor bg;
    ofColor fg;

private:
    float animation;
    ofTrueTypeFont myFont;
};