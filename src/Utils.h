#pragma once
#include "ofMain.h"

enum FONT_SIZE{
    BIG,
    MEDIUM,
    SMALL
};
enum ElementKind{
    DESTROYER_ELEMENT,
    TARGET_ELEMENT,
    LINKED_TARGET_ELEMENT
};
enum ButtonKind{
    NOT_BUTTON,
    RESTART,
    CREDITS
};

enum colorId{
    FG,
    BG,
    GAME_OBJ
};
enum SOUND_ID{
    TAP,
    LEVEL_COMPLETE,
    LEVEL_FAIL,
    MENU_STEP,
    TARGET,
    WRONG_TAP
};

static ofColor Colors[] = {ofColor(2,60,75), ofColor(255, 80, 100), ofColor(255)};

static float gauss(float val, float height, float width, float offset){
    return height / pow(2, pow( (val-offset)/width, 2));
};
static void drawCenterText(string str, int x, int y, ofTrueTypeFont *font, bool horiz, bool vertic){
    ofRectangle shape = font->getStringBoundingBox(str, 0, 0);
    if(horiz && vertic) font->drawString(str, x-(shape.width/2), y+(shape.height/2));
    else if(horiz) font->drawString(str, x-(shape.width/2), y);
    else if(vertic) font->drawString(str, x, y+(shape.height/2));
    else font->drawString(str, x, y);
}
static void drawCenterText(string str, int x, int y, ofTrueTypeFont *font){ drawCenterText(str, x, y, font, true, true); }
static void drawCenterText(string str, ofTrueTypeFont *font){ drawCenterText(str, ofGetWidth()/2, ofGetHeight()/2, font, true, true); }

class Utils{
public:
    static ofEvent<string> playSoundEventUtil;
};