#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fonts[BIG].loadFont("assets/fonts/Melbourne_light.otf", 100);
    fonts[MEDIUM].loadFont("assets/fonts/Melbourne_light.otf", 50);
    fonts[SMALL].loadFont("assets/fonts/Melbourne_light.otf", 30);

    // load sounds
    for (int i=0; i<5; i++) tapSounds[i].loadSound("assets/tapSounds/tap"+ofToString(i)+".mp3");
    
    ofBackground(0);
    
    // ofSetBackgroundAuto(false);
    // ofSetFrameRate(5);
    // ofSetLogLevel(OF_LOG_VERBOSE);
    
    // settings
    debug = false;
    connect = false;
    serverInterface = false;
    touchDebug = true;
    
    cmToPx = 104;
    cmToPx = 90;

    initEvents();
    if(connect){
        serverConnection.setup("10.206.104.38", 11999);
        cal.init(fonts);
    }
    else{
        cal.done = true;
        game.init(fonts);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(connect) serverConnection.update();

    // orientation fix
    if(ofxiOSGetGLView().frame.origin.x != 0 || ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width) ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);

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
    if(connect && serverInterface) serverConnection.drawInterface();
    if(debug){ ofSetColor(255); ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 500, 15); }
    if(!serverConnection.Connected && connect){
        ofRectangle shape = fonts[SMALL].getStringBoundingBox("You are not connected. Please check your network", 0, 0);
        fonts[SMALL].drawString("You are not connected. Please check your network", 1024-shape.width/2, 1450);
    }
}

void ofApp::exit(){}

void ofApp::touchDown(ofTouchEventArgs & touch){
    // on touch, send position to server for calinration. (if calibration is not done)
    if(connect && serverConnection.Connected && !cal.done) serverConnection.send("calibration:"+ofToString(touch.x)+","+ofToString(touch.y));
    if(touchDebug && !connect) onTapEvent(touch);
}

void ofApp::touchMoved(ofTouchEventArgs & touch){}
void ofApp::touchUp(ofTouchEventArgs & touch){}
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){}
void ofApp::touchCancelled(ofTouchEventArgs & touch){}
void ofApp::lostFocus(){}
void ofApp::gotFocus(){}
void ofApp::gotMemoryWarning(){}
void ofApp::deviceOrientationChanged(int newOrientation){}

void ofApp::initEvents(){
    if(connect){
        ofAddListener(serverConnection.serverEvent, this, &ofApp::onServerEvent);
        ofAddListener(serverConnection.deviceEvent, this, &ofApp::onDeviceEvent);
        ofAddListener(serverConnection.tapEvent, this, &ofApp::onTapEvent);
    }
    ofAddListener(PointElement::buttonEvent, this, &ofApp::onButton);
}

void ofApp::onServerEvent(string & e){ cout << "server event:" << e << endl; }
void ofApp::onDeviceEvent(string & e){ cout << "device event:" << e << endl; }

void ofApp::onTapEvent(ofVec2f &e){
    tapSounds[(int)ofRandom(5)].play();
    if(!cal.done) cal.step++;
    else{
        testPos.set(e.x, e.y);
        game.tap(e.x, e.y);
    }
}
void ofApp::onButton(ButtonKind & kind){
    if(kind==RESTART) game.levels[game.currentLevel].completed = true;
    else cout << "btn " << kind;
}
