#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Particle.h"
#include "Wave.h"

const int s = 158;
const int base = 256;

class Grid{
    public:
    Grid();
    void init(int squareSize);
    void update(vector<Wave> & waves);
    void draw();

    private:
    float ang;
    ofMesh mesh;
    vector<Particle> particles;
};