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
    transitionEnd = ofDist(0, 0, ofGetWidth()/2, ofGetHeight()/2)+50;
    transitionPos = 0;
    active = true;
    isInfoScreen = false;
}
void Game::tap(float x, float y){
    // if we are in an info screen
    if(isInfoScreen){
        transitionPos = transitionEnd+1;
        gotoNextLevel();
    }
    else{
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
            if(transitionPos < transitionEnd-50) transitionPos += (transitionEnd-transitionPos) / 20;
            
            // on when the transition circle is half-way to its destination, diplay infoScreen
            if(transitionPos > transitionEnd/2 && levels[nextLevel].targetCount>0) isInfoScreen = true;

            // if the next level has not targets, do not display the infoscreen
            else if(levels[nextLevel].targetCount==0) gotoNextLevel();
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
            float middle = transitionEnd/2;
            ofSetColor(Colors[GAME_OBJ], 255*(transitionPos-middle)/middle );
            
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
        else if(transitionPos > transitionEnd/2){ levels[nextLevel].draw(1); }
    }
}
void Game::gotoNextLevel(){
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