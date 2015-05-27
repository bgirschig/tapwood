#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "Obstacle.h"

class Level{
public:
    Level(string name);
   
    void update();

    void addPoint(float x, float y, ElementKind kind);
    void addPoint(float x, float y, string kind);
    string name;
    vector<Obstacle *> points;
    bool completed;
    
private:
    int targetCount;
};