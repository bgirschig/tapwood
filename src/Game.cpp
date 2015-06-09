#include "Game.h"


Game::Game(){
    active = false;
}

void Game::init(ofTrueTypeFont *_fonts){
    fonts = _fonts;
    
    ofBuffer buffer = ofBufferFromFile("Levels.lvl");
    while (!buffer.isLastLine()) {
        int currentLevel = levels.size()-1;
        string line = Poco::replace(buffer.getNextLine(), "\t\t", "\t"); // TODO: regex.
        line = Poco::replace(line, "\t\t", "\t");

        vector<string> parts = ofSplitString(line, "\t");
        if(parts[0]=="level") levels.push_back(Level(parts[1], fonts));
        else if(parts[0]=="point") levels[currentLevel].addPoint(parts[1], parts[2], parts[3]);
        else if(parts[0]=="line") levels[currentLevel].addLine(parts[1], parts[2], parts[3], parts[4]);
        else if(parts[0]=="title") levels[currentLevel].addTitle(parts[1], parts[2], parts[3], parts[4]);
        else if(parts[0]=="button") levels[currentLevel].addButton(parts[1], parts[2], parts[3], parts[4]);
    }
    
    // inits
    transitionTimer = 0;
    active = true;
}
void Game::tap(float x, float y){
    if(active) waves.push_back(Wave(x, y));
}

void Game::update(){
    if(currentLevel<levels.size()){
        // Update each wave
        int waveCount = waves.size();
        for(int i=0;i<waveCount;i++){
            // erase waves that are not alive
            if(!waves[i].alive || waves[i].force < 0.3){waves.erase(waves.begin()+i); waveCount--;}
            // update the others
            else waves[i].update(levels[currentLevel].points, levels[currentLevel].lines, 1-transitionTimer);
            // fade out if level is done
            if( levels[currentLevel].completed ) waves[i].fadeout = true;
        }
        
        levels[currentLevel].update();
        
        // current level is done
        if(levels[currentLevel].completed){
            if(transitionTimer < 1){
                transitionTimer+=0.07;
                levels[(currentLevel+1)%levels.size()].update();
            }
            else{
                levels[currentLevel].reset();
                for(int i=waveCount-1;i>0;i++){
                    waves.erase(waves.begin()+i);
                }
                currentLevel = (currentLevel+1)%levels.size();
                transitionTimer = 0;
            }
        }
    }
}
void Game::draw(){
    for(Wave &w : waves) w.draw();
    levels[currentLevel].draw(1);
    
    if(levels[currentLevel].completed){    // transition
        ofFill();ofSetColor(0,10,30,255*transitionTimer);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        levels[(currentLevel+1)%levels.size()].draw(transitionTimer);
    }
}