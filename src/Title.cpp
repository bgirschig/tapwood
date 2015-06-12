#include "Title.h"

Title::Title(string _text, int _x, int _y, ofTrueTypeFont *_font){
    font = _font;
    text = _text;
    ofRectangle shape = font->getStringBoundingBox(text, 0, 0);
    x = _x - shape.width/2;
    y = _y + shape.height/2;
}

void Title::draw(float opacity){
    ofSetColor(Colors[GAME_OBJ] * opacity);
    font->drawString(text, x, y);
}