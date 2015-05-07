//
//  Particle.h
//  tapwood
//
//  Created by bastien girschig on 07/05/2015.
//
//

#ifndef __tapwood__Particle__
#define __tapwood__Particle__

#include <stdio.h>
#include "ofMain.h"

class Particle
{
    public:
//    constructor
    Particle(float x, float y, float direction, float _speed);

//    variables
    ofVec2f position;
    ofVec2f speed;
    Boolean alive;

//    methods
    void update();
    void draw();
};



#endif /* defined(__tapwood__Particle__) */
