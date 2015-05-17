#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,10,30);
//  ofSetBackgroundAuto(false);
//  ofSetFrameRate(10);
    
    // server connection
    ofAddListener(serverConnection.serverEvent, this, &ofApp::onServerEvent);
    ofAddListener(serverConnection.deviceEvent, this, &ofApp::onDeviceEvent);
    ofAddListener(serverConnection.dataEvent, this, &ofApp::onDataEvent);

    serverConnection.setup("192.168.0.101", 11999);
//    serverConnection.setup("10.192.250.91", 11999);
//    serverConnection.setup("192.168.1.119", 11999);
    
    obstacles.push_back(new Obstacle(ofVec2f(500,300), DESTROYER_OBSTACLE));
    obstacles.push_back(new Obstacle(ofVec2f(900,600), DESTROYER_OBSTACLE));
}

//--------------------------------------------------------------
void ofApp::update(){
    serverConnection.update();
    
    // orientation fix
    if(ofxiOSGetGLView().frame.origin.x != 0 || ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width){
        ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);
    }
    
    // Update each wave
    int s = waves.size();
    for(int i=0;i<s;i++){
        if(!waves[i].alive){waves.erase(waves.begin()+i); s--;}
        else waves[i].update(obstacles);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    serverConnection.drawInterface();
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
    
    for(Wave &w : waves) w.draw();
    int s = obstacles.size();
    for (int i=0; i<s; i++) {
        obstacles[i]->draw();
    }
}

void ofApp::exit(){}

void ofApp::touchDown(ofTouchEventArgs & touch){
    // x, y, force, resolution
    waves.push_back( Wave(touch.x, touch.y, 200, 200) );
    if(serverConnection.Connected) serverConnection.send("screenTap");
}

void ofApp::touchMoved(ofTouchEventArgs & touch){}
void ofApp::touchUp(ofTouchEventArgs & touch){}
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){}
void ofApp::touchCancelled(ofTouchEventArgs & touch){}
void ofApp::lostFocus(){}
void ofApp::gotFocus(){}
void ofApp::gotMemoryWarning(){}
void ofApp::deviceOrientationChanged(int newOrientation){}

void ofApp::onServerEvent(string & e){
    cout << "server event:" << e << endl;
}
void ofApp::onDeviceEvent(string & e){
    cout << "device event:" << e << endl;
}
void ofApp::onDataEvent(string &e){
//    cout << "DATA: " << e << endl;
    if(e=="tap"){
        waves.push_back( Wave(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()), 40, 100) );
    }
}
