#pragma once

#include "ofMain.h"
#include "Utils.h"
#include <stdio.h>
#include "connection.h"

class Calibrator{
public:
    Calibrator();
    void init(ofTrueTypeFont *_fonts, connection *_client);
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
    ofTrueTypeFont *fonts;
    connection *client;
};