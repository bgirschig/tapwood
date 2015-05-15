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
    
    bool stopped = false;
    bool alive = false;
    
    private:
    float force;
    float speed;
    vector<Particle> particles;
    int resolution;
    ofMesh mesh;
    void killParticle(int index);
};