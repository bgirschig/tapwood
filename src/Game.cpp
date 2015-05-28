#include "Game.h"


Game::Game(){}
void Game::init(){
    currentLevel = 0;
    
    // first 'level'
    Level first = Level("start");
    first.specialLevel = 0;
    first.addPoint(ofGetHeight()/2, ofGetWidth()/2+100, TARGET_OBSTACLE); // restart button
    levels.push_back(first);
    
    // load levels
    XML.loadFile("mySettings.xml");
    XML.pushTag("levels");
    int lvlCount = XML.getNumTags("level");
    for(int l =0; l<lvlCount; l++){
        Level lvl = Level(XML.getValue("level:name", "no-name", l));
        XML.pushTag("level", l);
        int ptCount = XML.getNumTags("point");
        for (int p=0; p<ptCount; p++) lvl.addPoint(XML.getValue("point:pos:x",0,p), XML.getValue("point:pos:y",0,p), XML.getValue("point:kind","none",p) );
        XML.popTag();
        
        levels.push_back( lvl );
    }
    // last 'level'
    Level last = Level("you won");
    last.specialLevel = 1;
    last.addPoint(ofGetHeight()/2, ofGetWidth()/2+100, TARGET_OBSTACLE); // restart button
    levels.push_back(last);
    
    // inits
    transitionTimer = 0;
}
void Game::tap(float x, float y){
    waves.push_back(Wave(x, y));
}

void Game::update(){
    if(currentLevel<levels.size()){
        // Update each wave
        int waveCount = waves.size();
        for(int i=0;i<waveCount;i++){
            if(!waves[i].alive || waves[i].force < 0.3){waves.erase(waves.begin()+i); waveCount--;}
            else waves[i].update(levels[currentLevel].points, 1-transitionTimer);
            if( levels[currentLevel].completed ) waves[i].fadeout = true;
        }
        
        levels[currentLevel].update();
        
        if(levels[currentLevel].completed){                             // current level is done
            if(transitionTimer < 1){
                transitionTimer+=0.07;
                levels[(currentLevel+1)%levels.size()].update();
            }
            else{
                levels[currentLevel].reset();
                for(int i=waveCount-1;i>0;i++){
                    waves.erase(waves.begin()+i);
                    cout << "erase wave" << endl;
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
        ofSetColor(0,10,30,255*transitionTimer);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        levels[(currentLevel+1)%levels.size()].draw(transitionTimer);
    }
}