#include "Level.h"

Level::Level(string _name, ofTrueTypeFont *_fonts){
    cout << "creating level: " << _name << endl;
    
    name = _name;
    fonts = _fonts;
    
    targetCount = 0;
    specialLevel = -1; // false by default
    reset();
}

void Level::reset(){
    completed = false;
    intro = false;
    transitionAnimation = ofGetWidth()/1.5;
    for (int i=0; i<points.size(); i++) points[i]->reset();
}

void Level::addPoint(string x, string y, string kind){
    if(kind=="DESTROYER") points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), DESTROYER_ELEMENT));
    else if(kind=="TARGET"){
        points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), TARGET_ELEMENT));
        targetCount ++;
    }
    else if (kind=="CREDITS_BUTTON") points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), CREDITS_BUTTON));
}

void Level::addLine(string x1, string y1, string x2, string y2){
    lines.push_back( new LineElement(ofVec2f(ofToInt(x1), ofToInt(y1)), ofVec2f(ofToInt(x2),ofToInt(y2))) );
}
void Level::addTitle(string x, string y, string font, string text){
    if(font=="BIG") titles.push_back(new Title(text, ofToInt(x), ofToInt(y), &fonts[BIG]));
    else if(font=="MEDIUM") titles.push_back(new Title(text, ofToInt(x), ofToInt(y), &fonts[MEDIUM]));
    if(font=="SMALL") titles.push_back(new Title(text, ofToInt(x), ofToInt(y), &fonts[SMALL]));
}

void Level::update(){
    int validCount = 0;
    
    for (int i=0; i<points.size(); i++) if(points[i]->kind == TARGET_ELEMENT && points[i]->hasCollided) validCount++;
    if(targetCount>0 && validCount==targetCount) completed = true;
}

void Level::draw(float opacity){
    for (int i=0; i<points.size(); i++) points[i]->draw(opacity);
    for (int i=0; i<lines.size(); i++) lines[i]->draw(opacity);
    for (int i=0; i<titles.size(); i++) titles[i]->draw(opacity);
}