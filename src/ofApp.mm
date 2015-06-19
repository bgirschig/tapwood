#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fonts[BIG].loadFont("assets/fonts/Melbourne_light.otf", 100);
    fonts[MEDIUM].loadFont("assets/fonts/Melbourne_light.otf", 60);
    fonts[SMALL].loadFont("assets/fonts/Melbourne_light.otf", 40);

    // load sounds
    for (int i=0; i<4; i++) tapSounds[i].loadSound("assets/tapSounds/tap"+ofToString(i)+".mp3");
    wrongTapSound.loadSound("assets/singleSounds/wrong.mp3");
    targetReachedSound.loadSound("assets/singleSounds/tagetReached.mp3");
    targetDeactivateSound.loadSound("assets/singleSounds/targetDeactivate.mp3");
    levelValidSounds.loadSound("assets/singleSounds/levelComplete.mp3");
    levelFailSound.loadSound("assets/singleSounds/levelFail.mp3");
    stepSound.loadSound("assets/singleSounds/menuStep.mp3");
    
    ofBackground(0);

    // settings
    debug = false;
    connectedMode = false;
    serverInterface = false;
    simulateTap = true;
    game.simulateTouch = simulateTap;

    // events / sensors
    initEvents();
    ofxAccelerometer.setup();
    
    if(connectedMode){
        // serverConnection.setup("10.206.104.38", 11999); //lab
        serverConnection.setup("10.0.1.9", 11999); // ecal install

        cal.init(fonts, &serverConnection);
        serverConnection.send("calibration:start");
    }
    else{
        cal.done = true;
        game.init(fonts);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if(abs(ofxAccelerometer.getOrientation().x)>2 && game.active && connectedMode){
        serverConnection.send("calibration:start");
        game.active = false;
        cal.init(fonts, &serverConnection);
        for(int i=game.waves.size()-1; i>=0; i--) game.killWave(i);
    }
    
    // orientation fix
    if(ofxiOSGetGLView().frame.origin.x != 0 || ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width) ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);
    
    if(connectedMode) serverConnection.update();

    if(game.active) game.update();
    if(!cal.done) {
        cal.update();
        if(cal.done) game.init(fonts);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(debug){}
    if(!cal.done && serverConnection.Connected) cal.draw();
    if(game.active) game.draw();
    if(connectedMode && debug) serverConnection.drawInterface();
    if(debug){ ofSetColor(255); ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 500, 15); }
    if(!serverConnection.Connected && connectedMode){
        ofSetColor(0,30); ofFill(); ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(Colors[GAME_OBJ]);
        ofRectangle shape = fonts[SMALL].getStringBoundingBox("You are not connected. Please check your network", 0, 0);
        fonts[SMALL].drawString("You are not connected. Please check your network", 1024-shape.width/2, 1450);
    }
}

void ofApp::exit(){}

void ofApp::touchDown(ofTouchEventArgs & touch){
    // on touch, send position to server for calinration. (if calibration is not done)
    if(connectedMode && serverConnection.Connected && !cal.done) serverConnection.send("calibration:"+ofToString(touch.x)+","+ofToString(touch.y));
    else if(simulateTap) onTapEvent(touch);
    else if(hiddenControls){
        if(touch.x > ofGetWidth()-200) game.gotoNextLevel();
        else if(touch.x < 200) game.gotoPrevLevel();
    };
}

void ofApp::touchMoved(ofTouchEventArgs & touch){}
void ofApp::touchUp(ofTouchEventArgs & touch){}
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
}
void ofApp::touchCancelled(ofTouchEventArgs & touch){}
void ofApp::lostFocus(){}
void ofApp::gotFocus(){}
void ofApp::gotMemoryWarning(){}
void ofApp::deviceOrientationChanged(int newOrientation){}

void ofApp::initEvents(){
    if(connectedMode){
        ofAddListener(serverConnection.tapEvent, this, &ofApp::onTapEvent);
        ofAddListener(serverConnection.tapUpEvent, this, &ofApp::onTapUpEvent);
    }
    ofAddListener(Utils::playSoundEventUtil, this, &ofApp::onPlaySoundEvent);
}

void ofApp::onTapEvent(ofVec2f &e){
    if(!cal.done) cal.step++;
    else{
        testPos.set(e.x, e.y);
        game.tap(e.x, e.y);
    }
}
void ofApp::onTapUpEvent(bool &e){ }

void ofApp::onButton(ButtonKind & kind){
    if(kind==RESTART) game.levels[game.currentLevel].completed = true;
    else cout << "btn " << kind;
}
void ofApp::onPlaySoundEvent(string & e){
    cout << "play: " << e << endl;
    if(e == "tap") tapSounds[(int)floor(ofRandom(4))].play();
    else if(e == "wrong") wrongTapSound.play();
    else if(e == "targetReached") targetReachedSound.play();
    else if(e == "targetDeactivate") targetDeactivateSound.play();
    else if(e == "levelValid") levelValidSounds.play();
    else if(e == "levelFail") levelFailSound.play();
    else if(e == "menuStep") stepSound.play();
}
