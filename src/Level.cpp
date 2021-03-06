#include "Level.h"

Level::Level(string _name, string _minWaveCount, ofTrueTypeFont *_fonts, ofColor _bg){
    cout << "creating level: " << _name << endl;
    
    name = _name;
    fonts = _fonts;
    minWaveCount = ofToInt(_minWaveCount);
    bg = _bg;
    
    targetCount = 0;
    failed = false;
    reset();
}

void Level::reset(){
    completed = false;
    intro = false;
    transitionAnimation = ofGetWidth()/1.5;
    remainingWaves = minWaveCount;
    for (int i=0; i<points.size(); i++) points[i]->reset();
}

void Level::addPoint(string x, string y, string kind){
    if(kind=="DESTROYER") points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), DESTROYER_ELEMENT));
    else if(kind=="TARGET"){
        points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), TARGET_ELEMENT));
        targetCount ++;
    }
}

void Level::addLine(string x1, string y1, string x2, string y2){
    lines.push_back( new LineElement(ofVec2f(ofToInt(x1), ofToInt(y1)), ofVec2f(ofToInt(x2),ofToInt(y2))) );
}
void Level::addRotLine(string x1, string y1, string x2, string y2){
    lines.push_back( new LineElement(ofVec2f(ofToInt(x1), ofToInt(y1)), ofVec2f(ofToInt(x2),ofToInt(y2)), true) );
}

void Level::addChain(){
    chains.push_back(new Link());
    targetCount ++;
}
void Level::linkToLastChain(string x, string y){
    points.push_back(new PointElement(ofVec2f(ofToInt(x),ofToInt(y)), LINKED_TARGET_ELEMENT));
    chains[chains.size()-1]->add(points[points.size()-1]);
}

void Level::update(){
    int validCount = 0;
    
    for (int i=0; i<points.size(); i++) if(points[i]->kind == TARGET_ELEMENT && points[i]->valid) validCount++;
    for (int i=0; i<chains.size(); i++){
        chains[i]->update();
        if(chains[i]->valid) validCount++;
    }
    if(targetCount>0 && validCount==targetCount && !completed){
        string str = "levelValid"; ofNotifyEvent(Utils::playSoundEventUtil, str, this);
        cout << "level is done" << endl;
        completed = true;
    }
    for (int i=0; i<chains.size(); i++) chains[i]->update();
}

void Level::draw(float opacity, bool background){
    if(background) ofSetColor(bg, 255*opacity);ofFill();ofRect(0, 0, ofGetWidth(), ofGetHeight());
    for (int i=0; i<points.size(); i++) points[i]->draw(opacity);
    for (int i=0; i<lines.size(); i++) lines[i]->draw(opacity);
    for (int i=0; i<chains.size(); i++) chains[i]->draw(opacity);
    
    // wave counter
    if(minWaveCount != 0){
        ofSetColor(Colors[GAME_OBJ],255*opacity);
        string str;
        if(remainingWaves > 1) str = ofToString(remainingWaves) + " waves left";
        else if(remainingWaves == 1) str = "one wave left";
        else str = "no more waves";
        
        drawCenterText(str, ofGetWidth()/2, ofGetHeight()-50, &fonts[SMALL], true, false);
    }
    drawTuto(opacity);
}
void Level::draw(float opacity){ draw(opacity, true); }

void Level::drawTuto(float opacity){
    ofSetColor(Colors[GAME_OBJ], 255*opacity);
    if(name == "targets"){
        drawCenterText("These are targets", ofGetWidth()/2, 65, &fonts[MEDIUM]);
        drawCenterText("reach them to go to the next level", ofGetWidth()/2, 150, &fonts[SMALL]);
    }
    else if(name=="recalibration"){
        drawCenterText("Sometimes, the solution is outside the game zone", ofGetWidth()/2, 65, &fonts[MEDIUM]);
        drawCenterText("Just move the ipad, we'll do the rest", ofGetWidth()/2, 150, &fonts[SMALL]);
    }
    else if(name=="obstacles"){
        drawCenterText("If your wave touches an obstacle, it gets destroyed", ofGetWidth()/2, 65, &fonts[MEDIUM]);
        drawCenterText("make shure you avoid them", ofGetWidth()/2, 150, &fonts[SMALL]);
    }
    else if(name=="links") drawCenterText("Linked targets must be reached at the same time", ofGetWidth()/2, 65, &fonts[MEDIUM]);

    else if(name=="walls"){
        drawCenterText("Waves can't go through walls", ofGetWidth()/2, 65, &fonts[MEDIUM]);
        drawCenterText("go around them to reach your targets", ofGetWidth()/2, 150, &fonts[SMALL]);
    }
    else if(name=="wallHelp"){
        drawCenterText("Yet sometimes, walls can be helpful.", ofGetWidth()/2, 65, &fonts[MEDIUM]);
        drawCenterText("use them wisely", ofGetWidth()/2, 150, &fonts[SMALL]);
    }
}