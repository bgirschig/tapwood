#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Utils.h"

class LineElement {

public:
    LineElement();
    LineElement(ofVec2f _point1, ofVec2f _point2);
    LineElement(ofVec2f _point1, ofVec2f _point2, bool _rotate);
    void init(ofVec2f _point1, ofVec2f _point2, bool _rotate);
    
    ofVec3f pt1;
    ofVec3f pt2;
    ofVec2f local;
    ofVec2f normal;
    ofVec2f center;
    
    float dampening;
    float animFrame;

    // rotation
    ofMatrix4x4 rotationMatrix;
    bool rotate;
    float rotationPos;
    float length;
    
    // equation
    float a,b;
    
    void draw(float opacity);
private:
    void setEquation();
};