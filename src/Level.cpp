#include "Level.h"

Level::Level(string _name, string _minWaveCount, ofTrueTypeFont *_fonts){
    cout << "creating level: " << _name << endl;
    
    name = _name;
    fonts = _fonts;
    minWaveCount = _minWaveCount;
    
    targetCount = 0;
    
    reset();
    
    if(name=="test"){
        points.push_back(new PointElement(ofVec2f(100,100), LINKED_TARGET_ELEMENT));
        points.push_back(new PointElement(ofVec2f(700,400), LINKED_TARGET_ELEMENT));
        points.push_back(new PointElement(ofVec2f(500,1000), LINKED_TARGET_ELEMENT));
        
        links.push_back(Link());
        links[links.size()-1].add(points[0]);
        links[links.size()-1].add(points[1]);
        links[links.size()-1].add(points[2]);
        targetCount = 1;
    }
}

void Level::reset(){
    completed = false;
    intro = false;
    transitionAnimation = ofGetWidth()/1.5;
    waveCount = 0;
    for (int i=0; i<points.size(); i++) points[i]->reset();
}

void Level::addPoint(string x, string y, string kind){
    if(kind=="DESTROYER") points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), DESTROYER_ELEMENT));
    else if(kind=="TARGET"){
        points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), TARGET_ELEMENT));
        targetCount ++;
    }
}
void Level::addButton(string x, string y, string kind, string text){
    ofVec2f pos = ofVec2f(ofToInt(x), ofToInt(y));
    PointElement *p = new PointElement(pos, TARGET_ELEMENT);
    if(kind=="START") p->buttonKind = RESTART;
    else if(kind=="CREDITS") p->buttonKind = CREDITS;
    
    titles.push_back(new Title(text, pos.x, pos.y-60, &fonts[SMALL]));
    points.push_back(p);
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
    for (int i=0; i<links.size(); i++){
        links[i].update();
        if(links[i].valid) validCount++;
        cout << validCount << "/" << targetCount << endl;
    }
    
    if(targetCount>0 && validCount==targetCount){
        completed = true;
//        for (int i=0; i<points.size(); i++) points[i]->size+=2;
    }
    for (int i=0; i<links.size(); i++) links[i].update();
}

void Level::draw(float opacity){
    for (int i=0; i<points.size(); i++) points[i]->draw(opacity);
    for (int i=0; i<lines.size(); i++) lines[i]->draw(opacity);
    for (int i=0; i<titles.size(); i++) titles[i]->draw(opacity);
    for (int i=0; i<links.size(); i++) links[i].draw(opacity);
    
    // wave counter
    if(minWaveCount!="0"){
        ofSetColor(255,255,255,255*opacity);
        fonts[SMALL].drawString(ofToString(waveCount)+"/"+minWaveCount, ofGetWidth()/2-50, ofGetHeight()-30);
    }
}