#pragma once

#include <stdio.h>
#include "ofMain.h"

enum kinds{
    DESTROYER_OBSTACLE,
    TARGET_OBSTACLE
};

class Obstacle {
    public:
    
    Obstacle();
    Obstacle(ofVec2f position, int type);

    ofVec2f pos;
    int kind;
    bool hasCollided;
    
    bool collisionCheck(ofVec2f pt1, ofVec2f pt2, ofVec2f pt3, ofVec2f pt4);
    int getSide(ofVec2f a, ofVec2f b);
    void draw();
    
    // collision vars
    ofVec2f a, b, affine_segment, affine_point;
    int current_side;
};