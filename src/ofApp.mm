#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,10,30);
//  ofSetBackgroundAuto(false);
//  ofSetFrameRate(10);
    
    initServer();
    game.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    serverConnection.update();
    
    // orientation fix
    if(ofxiOSGetGLView().frame.origin.x != 0 || ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width){
        ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);
    }
    
    game.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 80, 100); ofFill();
    ofCircle(testPos.x, testPos.y, 10);
//    serverConnection.drawInterface();
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
    game.draw();
}

void ofApp::exit(){}

void ofApp::touchDown(ofTouchEventArgs & touch){
    if(serverConnection.Connected) serverConnection.send("screenTap");
    game.tap(touch.x, touch.y);
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
    serverConnection.setup("192.168.0.101", 11999);  // home
//    serverConnection.setup("10.192.250.112", 11999); // ecal
//    serverConnection.setup("192.168.1.119", 11999);  // ?
//    serverConnection.setup("192.168.0.11", 11999);   // camille
    ofAddListener(serverConnection.serverEvent, this, &ofApp::onServerEvent);
    ofAddListener(serverConnection.deviceEvent, this, &ofApp::onDeviceEvent);
    ofAddListener(serverConnection.dataEvent, this, &ofApp::onDataEvent);
}
void ofApp::onServerEvent(string & e){
    cout << "server event:" << e << endl;
}
void ofApp::onDeviceEvent(string & e){
    cout << "device event:" << e << endl;
}
void ofApp::onDataEvent(string &e){ 
    vector<string> data = ofSplitString(e, ",");

    testPos.set(ofToInt(data[0]), ofToInt(data[1]));
    game.tap(ofToInt(data[0]), ofToInt(data[1]));
}
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
