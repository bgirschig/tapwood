#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Utils.h"

class Title {

public:
    Title(string _text, int _x, int _y, ofTrueTypeFont *_font);
    void draw(float opacity);
    
private:
    string text;
    ofTrueTypeFont *font;
    int x;
    int y;

};