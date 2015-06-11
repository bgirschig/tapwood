#pragma once

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
    BG,
    FG,
    GAME_OBJ
};
static ofColor Colors[] = {ofColor(255,0,0), ofColor(0,100,0), ofColor(255,255,255)};

//2,60,75
//255, 80, 100
//218, 64, 71