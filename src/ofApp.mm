#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(80, 80, 80);
//    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
    // retina fix
    if(ofxiOSGetGLView().frame.origin.x != 0 || ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width){
        ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);
    }
    
    // Update each wave
    for(Wave &w : waves) w.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
    
    for(Wave &w : waves) w.draw();

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

    // x, y, force, resolution
    waves.push_back( Wave(touch.x, touch.y, 40, 600) );
    
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
