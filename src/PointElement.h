#pragma once

#include <stdio.h>
#include "ofMain.h"

enum ElementKind{
    DESTROYER_ELEMENT,
TARGET_ELEMENT
};

class PointElement {
    public:
    
    // constructors
    PointElement();
    PointElement(ofVec2f position, ElementKind type);

    // public vars
    ofVec2f pos;
    ElementKind kind;
    bool valid;
    bool hasCollided;
    
    // public functions
    bool collisionCheck(ofVec2f pt1, ofVec2f pt2, ofVec2f pt3, ofVec2f pt4);
    void collided();
    void draw(float opacity);
    void reset();
    
    private:
    int getSide(ofVec2f a, ofVec2f b);          // collision detection utils
    ofVec2f a, b, affine_segment, affine_point; //  --
    int current_side;                           //  --
    int animation;
    float secondaryAnim;
    float scale;
};