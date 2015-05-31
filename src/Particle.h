#pragma once

#include <stdio.h>

#include "ofMain.h"
#include "LineElement.h"
#include "PointElement.h"

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
    PointElement * blackHole;
    
    // methods
    void update(float speed);
    bool lineBounce(LineElement *l);
    void setEquation();
};