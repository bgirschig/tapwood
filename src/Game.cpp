#include "Game.h"


Game::Game(){
    active = false;
}

void Game::init(ofTrueTypeFont *_fonts){
    fonts = _fonts;
    
    // load levels
    ofBuffer buffer = ofBufferFromFile("assets/Levels.lvl");
    while (!buffer.isLastLine()) {
        int currentLevel = levels.size()-1;
        string line = Poco::replace(buffer.getNextLine(), "\t\t", "\t"); // TODO: regex.
        line = Poco::replace(line, "\t\t", "\t");

        vector<string> parts = ofSplitString(line, "\t");
        if(parts[0]=="level") levels.push_back(Level(parts[1], parts[2], fonts, Colors[(levels.size()-1)%2]));
        else if(parts[0]=="point") levels[currentLevel].addPoint(parts[1], parts[2], parts[3]);
        else if(parts[0]=="line") levels[currentLevel].addLine(parts[1], parts[2], parts[3], parts[4]);
        else if(parts[0]=="title") levels[currentLevel].addTitle(parts[1], parts[2], parts[3], parts[4]);
        else if(parts[0]=="button") levels[currentLevel].addButton(parts[1], parts[2], parts[3], parts[4]);
        else if(parts[0]=="chain") levels[currentLevel].addChain();
        else if(parts[0]=="->") levels[currentLevel].linkToLastChain(parts[1], parts[2]);
    }
    
    // inits
    transitionEnd_1 = ofDist(0, 0, ofGetWidth()/2, ofGetHeight()/2)+50;
    transitionEnd_2 = transitionEnd_1+200;
    
    transitionPos = 0;
    active = true;
    isInfoScreen = false;
}
void Game::tap(float x, float y){
    // if we are in an info screen
    if(isInfoScreen && transitionPos<=transitionEnd_1) transitionPos = transitionEnd_1+1;
    else if(transitionPos==0){
        overlayOpacity = min(overlayOpacity+50, 150);

        if(active && !levels[currentLevel].completed){
            waves.push_back(Wave(x, y));
            levels[currentLevel].waveCount++;
        }
    }
}

void Game::update(){
    if(overlayOpacity>3) overlayOpacity -=4;
    realOpacity += (overlayOpacity-realOpacity)/3;
    
    if(currentLevel<levels.size()){
        // Update each wave
        int waveCount = waves.size();
        
        for(int i=waveCount-1; i>=0; i--){
            // erase waves that are not alive
            if(!waves[i].alive || waves[i].force < 0.3) killWave(i);
            
            // update the alive ones
            else waves[i].update(levels[currentLevel].points, levels[currentLevel].lines, 1);
            
            // fade out, slow and deactivate if level is done
            if( levels[currentLevel].completed ) waves[i].fadeout = true;
        }
        
        levels[currentLevel].update();

        // if current level is done, transition
        if(levels[currentLevel].completed){
            nextLevel = (currentLevel+1) % levels.size();
            
            // animate transition
            if(transitionPos < transitionEnd_1) transitionPos += (transitionEnd_1-transitionPos) / 20;
//            else transitionPos = transitionEnd_1;
            
            // when the transition circle is half-way to its destination, start displaying infoScreen
            if(transitionPos > transitionEnd_1/2) isInfoScreen = true;
        }
    }
}

void Game::draw(){
    levels[currentLevel].draw(1);
    for(Wave &w : waves) w.draw();
    
    ofSetColor(Colors[GAME_OBJ], realOpacity); ofFill(); ofRect(0, 0, ofGetWidth(), ofGetWidth());
    
    // transition
    if(levels[currentLevel].completed){
        ofSetCircleResolution(60);
        ofFill(); ofSetColor(levels[nextLevel].bg); ofCircle(ofGetWidth()/2, ofGetHeight()/2, transitionPos);
        ofSetCircleResolution(10);
        
        if(isInfoScreen){
            float opacity = 255 * (transitionPos-(transitionEnd_1/2)) / (transitionEnd_1/2);
            
            if(levels[nextLevel].targetCount==0) levels[nextLevel].draw(opacity, false);
            else{
                ofSetColor(Colors[GAME_OBJ],  opacity);
                string txt = "LEVEL "+ofToString(nextLevel);
                ofRectangle shape = fonts[BIG].getStringBoundingBox(txt, 0, 0);
                fonts[BIG].drawString(txt, (ofGetWidth()-shape.width)/2, ofGetHeight()/2);
                
                txt = ofToString(levels[nextLevel].targetCount)+" waves";
                shape = fonts[MEDIUM].getStringBoundingBox(txt, 0, 0);
                fonts[MEDIUM].drawString(txt, (ofGetWidth()-shape.width)/2, ofGetHeight()/2 + 100);
                
                txt = "tap to continue";
                shape = fonts[SMALL].getStringBoundingBox(txt, 0, 0);
                fonts[SMALL].drawString(txt, (ofGetWidth()-shape.width)/2, ofGetHeight()-50);
            }
        }
        
        // transition step 2
        if(transitionPos > transitionEnd_1 && transitionPos < transitionEnd_2-2){
            transitionPos+=(transitionEnd_2-transitionPos)/10;
            levels[nextLevel].draw((transitionPos-transitionEnd_1)/(transitionEnd_2-transitionEnd_1));

            if(transitionPos >= transitionEnd_2-10) gotoNextLevel();
        }
    }
}
void Game::gotoNextLevel(){
    cout << "gotoNextLevel" << endl;
    levels[currentLevel].reset();
    for(int i=waves.size()-1; i>=0; i--) killWave(i);
    transitionPos = 0;
    currentLevel = nextLevel;
    isInfoScreen = false;
}
void Game::killWave(int i){
    waves[i].kill();
    waves.erase(waves.begin()+i);
}