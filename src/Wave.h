#pragma once

#include <stdio.h>

#include "ofMain.h"
#include "Particle.h"
#include "PointElement.h"
#include "LineElement.h"

class Wave {
    public:
    
    // constructors
    Wave();
    Wave(float x, float y);
    
    // methods
    void test();
    void update(vector<PointElement *>& points, vector<LineElement *>& lines, float opacity);
    void draw();
    
    vector<Particle> particles;
    bool slow = false;
    bool randomise = false;
    bool alive = false;
    bool fadeout = false;
    PointElement * blackHole;
    float force;
    double pitch;
    
    private:
    float speed;
    int resolution;
    ofMesh mesh;
    void killParticle(int index);
    bool rayIntersects(int x, int y, float angle);
    int screenW, screenH;
};