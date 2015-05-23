#include "Game.h"


Game::Game(){}
void Game::init(){
    XML.loadFile("mySettings.xml");
    cout << "settings version: " << XML.getValue("version", "not set") << endl;

    int lvlCount = XML.getNumTags("levels:level");
    for(int l =0; l<lvlCount; l++){
        XML.pushTag("levels:level", l);
        string name = XML.getValue("level:name", "no-name", l);
        
        int ptCount = XML.getNumTags("level:point");
        cout << "level " << name << " has " << ptCount << " points:\n";
        for (int p=0; p<ptCount; p++) {
            XML.pushTag("level:point");
            cout << XML.getValue("point:kind","none",p) << "("<<XML.getValue("point:pos:x",0,p) << "," << XML.getValue("point:pos:y",0,p) << ")" << endl;
            XML.popTag();
        }
        XML.popTag();
    }
    
    levels.push_back(Level("bibi"));
    obstacles.push_back(new Obstacle(ofVec2f(500,300), DESTROYER_OBSTACLE));
    obstacles.push_back(new Obstacle(ofVec2f(900,600), TARGET_OBSTACLE));
    obstacles.push_back(new Obstacle(ofVec2f(1200,900), TARGET_OBSTACLE));
    obstacles.push_back(new Obstacle(ofVec2f(50,1000), TARGET_OBSTACLE));
}
void Game::tap(float x, float y){
    waves.push_back(Wave(x, y, 200, 200));
}
void Game::update(){
    // Update each wave
    int s = waves.size();
    for(int i=0;i<s;i++){
        if(!waves[i].alive){waves.erase(waves.begin()+i); s--;}
        else waves[i].update(obstacles);
    }
}
void Game::draw(){
    for(Wave &w : waves) w.draw();
    for (int i=0; i<obstacles.size(); i++) obstacles[i]->draw();
}