//
//  Wave.h
//  tapwood
//
//  Created by bastien girschig on 07/05/2015.
//
//

#ifndef __tapwood__Wave__
#define __tapwood__Wave__

#include <stdio.h>
#include <vector>
#include "Particle.h"

class Wave{
    public:
    Wave();
    Wave(ofVec2f _position, float _force, int _resolution);
    
    float force;
    vector<Particle> particles;
    int resolution;

    void update();
    void draw();
};


#endif /* defined(__tapwood__Wave__) */