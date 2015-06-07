#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,10,30);
//  ofSetBackgroundAuto(false);
//  ofSetFrameRate(5);
    
    // settings
    debug = true;
    connect = true;
    serverInterface = false;
    cmToPx = 104;
    cmToPx = 90;

    if(connect) initServer();
    cal.init();
//    game.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(connect) serverConnection.update();
    
    // orientation fix
    if(ofxiOSGetGLView().frame.origin.x != 0 || ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width){
        ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);
    }

    if(game.active) game.update();
    if(!cal.done) {
        cal.update();
        if(cal.done) game.init();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(debug){
        ofSetColor(255, 80, 100); ofFill();
        ofCircle(testPos.x, testPos.y, 10);
        ofLine(ofGetWidth()/2, ofGetHeight()/2, testPos.x, testPos.y);
    }
    if(connect && serverInterface) serverConnection.drawInterface();
    if(debug){ofSetColor(255);ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);}
    if(game.active) game.draw();
    
    if(!cal.done && serverConnection.Connected) cal.draw();
}

void ofApp::exit(){}

void ofApp::touchDown(ofTouchEventArgs & touch){
    if(connect && serverConnection.Connected && !cal.done){
        serverConnection.send("calibration:"+ofToString(touch.x)+","+ofToString(touch.y));
        cal.step++;
    }
//    game.tap(touch.x, touch.y);
}

void ofApp::touchMoved(ofTouchEventArgs & touch){}
void ofApp::touchUp(ofTouchEventArgs & touch){}
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){}
void ofApp::touchCancelled(ofTouchEventArgs & touch){}
void ofApp::lostFocus(){}
void ofApp::gotFocus(){}
void ofApp::gotMemoryWarning(){}
void ofApp::deviceOrientationChanged(int newOrientation){}

void ofApp::initServer(){
    serverConnection.setup("10.206.104.38", 11999);
    

    ofAddListener(serverConnection.serverEvent, this, &ofApp::onServerEvent);
    ofAddListener(serverConnection.deviceEvent, this, &ofApp::onDeviceEvent);
    ofAddListener(serverConnection.dataEvent, this, &ofApp::onDataEvent);
    ofAddListener(serverConnection.tapEvent, this, &ofApp::onTapEvent);
}
void ofApp::onServerEvent(string & e){
    cout << "server event:" << e << endl;
}
void ofApp::onDeviceEvent(string & e){
    cout << "device event:" << e << endl;
}
void ofApp::onDataEvent(string &e){
    vector<string> data = ofSplitString(e, ",");
    if(data.size()==2){
        testPos.set(ofToInt(data[0])*cmToPx, ofToInt(data[1])*cmToPx);
        game.tap(ofToInt(data[0])*cmToPx, ofToInt(data[1])*cmToPx);
    }
}
void ofApp::onTapEvent(ofVec2f &e){
    cout << "tap event: " << e;
    testPos.set(e.x, e.y);
    game.tap(e.x, e.y);
}

// dafuq is this? oftostring equivalent?
void split(const string& s, char c, vector<string>& v) {
    string::size_type i = 0;
    string::size_type j = s.find(c);
    
    while (j != string::npos) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);
        
        if (j == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}
