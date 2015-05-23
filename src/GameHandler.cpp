#include "GameHandler.h"

GameHandler::GameHandler(){}

void GameHandler::init(){
//    string message = "";
//    if( XML.loadFile("mySettings.xml") ) message = "mySettings.xml loaded from data folder!";
//    else message = "unable to load mySettings.xml check data/ folder";
//    cout << message << endl;
    Wave test = Wave(0, 0, 10, 10);
}
void GameHandler::onTap(float x, float y){
//    waves.push_back( Wave(x, y, 200, 200) );
}
void GameHandler::update(){
    int s = waves.size();
//    for(int i=0;i<s;i++){
//        if(!waves[i].alive){
//            waves.erase(waves.begin()+i);
//            s--;
//        }
//        else waves[i].update(obstacles);
//    }
}
void GameHandler::draw(){
    
}