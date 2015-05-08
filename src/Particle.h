#pragma once

#include <stdio.h>
#include "ofMain.h"

class Particle : public ofVec2f
{
    public:
    Particle(float _x, float _y, float direction, float _speed);

    // variables
    ofVec2f position;
    ofVec2f speed;
    bool alive;

    // methods
    void update();
    void draw();
};