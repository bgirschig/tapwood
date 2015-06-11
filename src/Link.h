#pragma once
#include "PointElement.h"

#include <stdio.h>

class Link{
public:
    Link();
    void update();
    void draw(float opacity);
    
    float animation;
    vector<PointElement> elements;
};