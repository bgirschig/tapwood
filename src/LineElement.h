#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Utils.h"

class LineElement {

public:
    LineElement();
    LineElement(ofVec2f _point1, ofVec2f _point2);
    
    ofVec2f pt1;
    ofVec2f pt2;
    ofVec2f local;
    ofVec2f normal;
    
    float dampening;
    float animFrame;
    
    // equation
    float a,b;
    
    void draw(float opacity);
private:
    void setEquation();
};