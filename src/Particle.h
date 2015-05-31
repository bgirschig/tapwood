#pragma once

#include <stdio.h>

#include "ofMain.h"
#include "LineElement.h"

class Particle
{
    public:
    Particle(float _x, float _y, double direction, float _speed);

    // variables
    ofVec2f position;
    ofVec2f pPosition;
    ofVec2f speed;
    bool alive;
    bool killWave;
    bool isNextKilled;
    bool isEdge;
    
    // methods
    void update(float speed);
    void debugDraw();
    void lineBounce(LineElement *l);
    void setEquation();
};