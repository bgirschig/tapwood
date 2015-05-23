#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "Obstacle.h"

class Level{
public:
    Level(string name);
    
    void addPoint(Obstacle point);
};