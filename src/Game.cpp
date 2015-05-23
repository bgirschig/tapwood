#include "Game.h"


Game::Game(){}
void Game::init(){
    levels.push_back(Level());
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