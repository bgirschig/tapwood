#include "Calibrator.h"

Calibrator::Calibrator(){}

void Calibrator::init(){
    step = 0;
    animation = 0;
    done = false;
    myFont.loadFont("Melbourne_light.otf", 60);
    glEnable(GL_LINE_SMOOTH);
}

void Calibrator::onCalibrationPoint(){
    step++;
//    animation = 0;
};
void Calibrator::update(){
    bg = ofColor(fmod(floor(step/3),2)*255);
    fg = ofColor((1-fmod(floor(step/3),2))*255);
    
    if(next) animation = 0;
    next = false;
    
    // opening
    if(step%3 == 0){
        if(animation<0.15) animation += (0.16-animation)/10;
        else step++;
    }
    // valid
    else if(step%3 == 2){
        if(animation<0.97) animation += (1-animation)/15;
        else{
            if(step==11) done = true;
            else{
                step++;
                next = true;
            }
        }
    }
}
void Calibrator::draw(){
    
    // background
    ofSetColor(bg);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    // circle
    ofSetCircleResolution(60);
    ofSetColor(fg);
    ofCircle(fmod(floor(step/3),2)*ofGetWidth(), floor(step/6)*ofGetHeight(), animation*ofGetWidth()*1.3);

    // text
    ofRectangle shape;
    string s;
    ofSetColor(fg);
    if(step<3){
        s = "First, we need to do a little calibration:";
        shape = myFont.getStringBoundingBox(s, ofGetWidth()/2, ofGetWidth()/2);
        myFont.drawString(s, shape.x-shape.width/2, shape.y-shape.height/2-3*myFont.getLineHeight());
        s = "Place the ipad on the table";
        shape = myFont.getStringBoundingBox(s, ofGetWidth()/2, ofGetWidth()/2);
        myFont.drawString(s, shape.x-shape.width/2, shape.y-shape.height/2-2*myFont.getLineHeight());
        s = "then touch the white circle";
        shape = myFont.getStringBoundingBox(s, ofGetWidth()/2, ofGetWidth()/2);
        myFont.drawString(s, shape.x-shape.width/2, shape.y-shape.height/2-myFont.getLineHeight());
    }
    
    else if(step<9){
        if(fg==0xffffff) s = "touch the white circle";
        else s = "now touch the black circle";
        shape = myFont.getStringBoundingBox(s, ofGetWidth()/2, ofGetWidth()/2);
        myFont.drawString(s, shape.x-shape.width/2, shape.y-shape.height/2-myFont.getLineHeight());
    }
    else{
        s = "... etc";
        shape = myFont.getStringBoundingBox(s, ofGetWidth()/2, ofGetWidth()/2);
        myFont.drawString(s, shape.x-shape.width/2, shape.y-shape.height/2-myFont.getLineHeight());
    }
}