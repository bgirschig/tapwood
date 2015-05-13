#pragma once

#include <stdio.h>
#include "ofMain.h"

class Wave;

class Particle
{
    public:
    Particle(Wave * _w, int index, float _x, float _y, double direction, float _speed);

    // variables
    ofVec2f position;
    ofVec2f anchor;
    ofVec2f speed;
    bool alive;

    // methods
    void update();
    
    void applyForce(ofVec2f force);
    
    Wave * wave;
};