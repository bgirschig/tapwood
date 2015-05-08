#pragma once

#include <stdio.h>
#include "Particle.h"

class Wave{
    public:
    
    // constructors
    Wave();
    Wave(float x, float y, float _force, int _resolution);
    
    // methods
    void update();
    void draw();
    
    // vars
    private:
    float force;
    vector<Particle> particles;
    int resolution;
};