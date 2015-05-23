#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,10,30);
//  ofSetBackgroundAuto(false);
//  ofSetFrameRate(10);
    
    // server connection
    initServer();

    game.init();
}

//--------------------------------------------------------------
void ofApp::update(){
//    serverConnection.update();
    
    // orientation fix
    if(ofxiOSGetGLView().frame.origin.x != 0 || ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width){
        ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);
    }
    
    game.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
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
    //    serverConnection.setup("192.168.0.101", 11999);  // home
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
//    cout << "DATA: " << e << endl;
//    if(e=="tap"){
//        waves.push_back( Wave(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()), 40, 100) );
//    }
}
