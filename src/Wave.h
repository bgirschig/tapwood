#pragma once

#include <stdio.h>
#include "Particle.h"
#include "Obstacle.h"

class Wave {
    public:
    
    // constructors
    Wave();
    Wave(float x, float y, float _force, int _resolution);
    
    // methods
    void update(Obstacle & obst);
    void draw();
    
    vector<Particle> particles;
    bool slow = false;
    bool randomise = false;
    bool alive = false;
    
    private:
    float force;
    float speed;
    int resolution;
    ofMesh mesh;
    void killParticle(int index);
};