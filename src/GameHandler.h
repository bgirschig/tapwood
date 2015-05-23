#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Level.h"

class GameHandler {
public:
    
    // constructors
    GameHandler();
    void init();
    
    vector<Level> levels;
};