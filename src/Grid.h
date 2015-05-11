#pragma once

#include <stdio.h>
#include "ofMain.h"

const int s = 158;
const int base = 256;

class Grid{
    public:
    Grid();
    void init(int squareSize);
    void update();
    void draw();

    private:
    float ang;
    ofMesh mesh;
};