#pragma once
#include "ofMain.h"
#include "Utils.h"
#include <stdio.h>

class Button{
public:
    Button(string _text, int _x, int _y, ButtonKind _action, ofTrueTypeFont *_font);
    void draw();
private:
    ofTrueTypeFont * font;
    string text;
    int x, y;
    ButtonKind action;
    ofEvent<ButtonKind> buttonEvent;
};