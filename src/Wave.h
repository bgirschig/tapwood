#pragma once

#include <stdio.h>

#include "ofMain.h"
#include "Particle.h"
#include "Obstacle.h"

class Wave {
    public:
    
    // constructors
    Wave();
    Wave(float x, float y);
    
    // methods
    void test();
    void update(vector<Obstacle *>& obstacles, float opacity);
    void draw();
    
    vector<Particle> particles;
    bool slow = false;
    bool randomise = false;
    bool alive = false;
    bool fadeout = false;
    Obstacle * blackHole;
    float force;
    
    private:
    float speed;
    int resolution;
    ofMesh mesh;
    void killParticle(int index);
};