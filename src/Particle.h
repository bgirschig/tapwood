#pragma once

#include <stdio.h>
#include "ofMain.h"

class Particle
{
    public:
    // constructor
    Particle(float x, float y, float direction, float _speed);

    // variables
    ofVec2f position;
    ofVec2f speed;
    bool alive;

    // methods
    void update();
    void draw();
};