#include "Game.h"


Game::Game(){}
void Game::init(){
    currentLevel = 1;
    
    XML.loadFile("mySettings.xml");

    XML.pushTag("levels");
    int lvlCount = XML.getNumTags("level");
    
    for(int l =0; l<lvlCount; l++){
        levels.push_back( Level(XML.getValue("level:name", "no-name", l)) );

        XML.pushTag("level", l);
        int ptCount = XML.getNumTags("point");
        for (int p=0; p<ptCount; p++) {
            levels[l].addPoint(XML.getValue("point:pos:x",0,p), XML.getValue("point:pos:y",0,p), XML.getValue("point:kind","none",p) );
        }
        XML.popTag();
    }
}
void Game::tap(float x, float y){
    waves.push_back(Wave(x, y, 200, 200));
}

void Game::update(){
    // Update each wave
    int s = waves.size();
    for(int i=0;i<s;i++){
        if(!waves[i].alive){waves.erase(waves.begin()+i); s--;}
        else waves[i].update(levels[currentLevel].points);
        
        levels[currentLevel].update();
        if(levels[currentLevel].completed) currentLevel ++;
    }
}
void Game::draw(){
    for(Wave &w : waves) w.draw();
    for (int i=0; i<levels[currentLevel].points.size(); i++) levels[currentLevel].points[i]->draw();
}