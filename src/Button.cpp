#include "Button.h"

Button::Button(string _text, int _x, int _y, ButtonKind _action, ofTrueTypeFont *_font){
    text = text;
    font = _font;
    ofRectangle shape = font->getStringBoundingBox(text, 0, 0);
    x = _x-shape.width;
    y = _y;
}
void Button::draw(){
    ofCircle(x, y, 10);
}