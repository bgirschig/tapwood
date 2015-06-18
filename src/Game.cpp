#include "Game.h"

Game::Game(){
    active = false;
}

void Game::init(ofTrueTypeFont *_fonts){
    fonts = _fonts;
    
    // load levels
    ofBuffer buffer = ofBufferFromFile("assets/levels-3.lvl");
    
    while (!buffer.isLastLine()) {
        int currentLevel = levels.size()-1;

        string line = Poco::replace(buffer.getNextLine(), "\t\t", "\t"); // TODO: regex.
        line = Poco::replace(line, "\t\t", "\t");

        vector<string> parts = ofSplitString(line, "\t");
        if(parts[0]=="level") levels.push_back(Level(parts[1], parts[2], fonts, Colors[(levels.size()-1)%2]));
        else if(parts[0]=="point") levels[currentLevel].addPoint(parts[1], parts[2], parts[3]);
        else if(parts[0]=="line") levels[currentLevel].addLine(parts[1], parts[2], parts[3], parts[4]);
        else if(parts[0]=="rotLine") levels[currentLevel].addRotLine(parts[1], parts[2], parts[3], parts[4]);
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
    wrongCounter = 0;
}
void Game::tap(float x, float y){
    // on tap on an info screen, start the second animation
    if(isInfoScreen && transitionPos<=transitionEnd_1){
        string str = "menuStep"; ofNotifyEvent(Utils::playSoundEventUtil, str, this);
        transitionPos = transitionEnd_1+1;
    }
    
    // on tap when no overlay is displayed
    else if(transitionPos==0){
        if(active &&                                                                // if game is active
           !levels[currentLevel].completed &&                                       // ...and level is not done yet
           (levels[currentLevel].remainingWaves > 0 || simulateTouch) &&                               // ...and player still has waves
           (x<0 || x>ofGetWidth() || y<0 || y>ofGetHeight() || simulateTouch))      // ... and touch is out of screen
        {
                overlayOpacity = min(overlayOpacity+100, 200);     // Then, create a wave
                waves.push_back(Wave(x, y));
                levels[currentLevel].remainingWaves--;
                string val = "tap"; ofNotifyEvent(Utils::playSoundEventUtil, val, this);
        }
        // wrong tap (in-screen, no more waves...)
        else{
            string val = "wrong"; ofNotifyEvent(Utils::playSoundEventUtil, val, this);

            wrongCounter += 50;
            if(wrongCounter >= 75){
                levels[currentLevel].reset();
                for(int i=waves.size()-1; i>=0; i--) killWave(i);
                wrongCounter = 0;
            }
            
        }
    }
    // on tap, when the 'failed' overlay is displayed
    else if(levels[currentLevel].failed){
        levels[currentLevel].reset();
        if(transitionPos<=transitionEnd_1) transitionPos = transitionEnd_1+1;
    }
}

void Game::update(){
    if(wrongCounter>0) wrongCounter--;
    // flash overlay
    if(overlayOpacity>3) overlayOpacity -=4;
    realOpacity += (overlayOpacity-realOpacity)/3;
    
    if(currentLevel<levels.size()){
        // Update each wave
        for(int i = waves.size()-1; i>=0; i--){
            // erase waves that are not alive
            if(!waves[i].alive || waves[i].force < 0.3) killWave(i);
            
            // update the alive ones
            else waves[i].update(levels[currentLevel].points, levels[currentLevel].lines, 1);
        }
        
        // update level
        levels[currentLevel].update();

        nextLevel = (currentLevel+1) % levels.size();
        
        // victory handling
        if(levels[currentLevel].completed){
            // animate transition
            if(transitionPos < transitionEnd_1) transitionPos += (transitionEnd_1-transitionPos) / 20;
            
            // when the transition circle is half-way to its destination, start displaying infoScreen
            if(transitionPos > transitionEnd_1/2) isInfoScreen = true;
        }
        
        // failure handling
        else if(levels[currentLevel].remainingWaves == 0 && waves.size()==0 && !levels[currentLevel].failed){
            levels[currentLevel].failed = true;
            string str = "levelFail"; ofNotifyEvent(Utils::playSoundEventUtil, str, this);
        }
        if(levels[currentLevel].failed){
            if(transitionPos < transitionEnd_1) transitionPos += (transitionEnd_1-transitionPos) / 20;
            else if(transitionPos > transitionEnd_1){
                transitionPos += (transitionEnd_2-transitionPos) / 15;
                if(transitionPos>=transitionEnd_2-10){
                    levels[currentLevel].failed = false;
                    transitionPos = 0;
                }
            }
        }
    }
}

void Game::draw(){
    if(levels.size()>0){
        levels[currentLevel].draw(1);
        for(Wave &w : waves) w.draw();
        
        ofSetColor(Colors[GAME_OBJ], realOpacity); ofFill(); ofRect(0, 0, ofGetWidth(), ofGetWidth());
        
        // next Level transition
        if(levels[currentLevel].completed){
            ofSetCircleResolution(60);
            ofFill(); ofSetColor(levels[nextLevel].bg); ofCircle(ofGetWidth()/2, ofGetHeight()/2, transitionPos);
            
            // info screen for next level
            if(isInfoScreen){
                float opacity = 255 * (transitionPos-(transitionEnd_1/2)) / (transitionEnd_1/2);

                if(levels[nextLevel].targetCount==0) levels[nextLevel].draw(opacity, false);
                else{
                    ofSetColor(Colors[GAME_OBJ],  opacity);
                    string txt = "LEVEL "+ofToString(nextLevel+1);
                    ofRectangle shape = fonts[BIG].getStringBoundingBox(txt, 0, 0);
                    fonts[BIG].drawString(txt, (ofGetWidth()-shape.width)/2, ofGetHeight()/2);
                    
                    txt = ofToString(levels[nextLevel].minWaveCount)+" wave";
                    if(levels[nextLevel].minWaveCount > 1) txt+= "s";
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

                if(transitionPos >= transitionEnd_2-10)gotoNextLevel();
            }
        }
        // 'you failed' screen
        else if(levels[currentLevel].failed){
            if(transitionPos > transitionEnd_1/2){
                float opacity;
                if(transitionPos<transitionEnd_1) opacity = 255 * (transitionPos-(transitionEnd_1/2)) / (transitionEnd_1/2);
                else opacity = 255 - 255 * ((transitionPos-transitionEnd_1)/(transitionEnd_2-transitionEnd_1));
                
                ofFill(); ofSetColor(10,opacity/2); ofRect(0, 0, ofGetWidth(), ofGetHeight());
                string txt = "you failed. tap to retry";
                ofSetColor(Colors[GAME_OBJ], opacity);
                fonts[BIG].drawString(txt, (ofGetWidth()-fonts[BIG].getStringBoundingBox(txt, 0, 0).width)/2, ofGetHeight()/2);
            }
        }
    }
}

void Game::gotoNextLevel(){
    cout << "gotoNext" << endl;
    levels[currentLevel].reset();
    for(int i=waves.size()-1; i>=0; i--) killWave(i);
    transitionPos = 0;
    currentLevel = nextLevel;
    isInfoScreen = false;
}
void Game::gotoPrevLevel(){
    cout << "gotoPrev" << endl;
    levels[currentLevel].reset();
    for(int i=waves.size()-1; i>=0; i--) killWave(i);
    transitionPos = 0;
    if(currentLevel>0) currentLevel--;
    isInfoScreen = false;
}
void Game::killWave(int i){
    waves[i].kill();
    waves.erase(waves.begin()+i);
}