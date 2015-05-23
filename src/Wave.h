#pragma once

#include <stdio.h>

#include "ofMain.h"
#include "Particle.h"
#include "Obstacle.h"

class Wave {
    public:
    
    // constructors
    Wave();
    Wave(float x, float y, float _force, int _resolution);
    
    // methods
    void test();
    void update(vector<Obstacle *> obstacles);
    void draw();
    
    vector<Particle> particles;
    bool slow = false;
    bool randomise = false;
    bool alive = false;
    Obstacle * blackHole;
    
    private:
    float force;
    float speed;
    int resolution;
    ofMesh mesh;
    void killParticle(int index);
};