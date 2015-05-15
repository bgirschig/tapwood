#pragma once

#include <stdio.h>
#include "ofMain.h"

class Wave;

class Particle
{
    public:
    Particle(int index, float _x, float _y, double direction, float _speed);

    // variables
    ofVec2f position;
    ofVec2f anchor;
    ofVec2f speed;
    bool alive;
    bool killWave;
    
    // methods
    void update(float speed);
    
    void applyForce(ofVec2f force);
};