#pragma once

#include <stdio.h>
#include "Particle.h"

class Wave {
    public:
    
    // constructors
    Wave();
    Wave(float x, float y, float _force, int _resolution);
    
    // methods
    void update();
    void draw();
    
    void hello();
    
    // vars
    int test = 4;
    private:
    float force;
    vector<Particle> particles;
    int resolution;
    ofMesh mesh;
};