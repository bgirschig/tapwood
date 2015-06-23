#include "Calibrator.h"

Calibrator::Calibrator(){}

void Calibrator::init(ofTrueTypeFont *_fonts, connection *_client){
    step = 0;
    animation = 0;
    done = false;
    fonts = _fonts;
    glEnable(GL_LINE_SMOOTH);
    client = _client;
    client->send("calibration:start");
}

void Calibrator::onCalibrationPoint(){ step++; };
void Calibrator::update(){
    bg = Colors[(int)(  fmod(floor(step/3), 2))];
    fg = Colors[(int)(1-fmod(floor(step/3), 2))];
    
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
    ofSetColor(bg);ofFill();
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    // circle
    ofSetCircleResolution(60);
    ofSetColor(fg);ofFill();
    ofCircle(fmod(floor(step/3),2)*ofGetWidth(), floor(step/6)*ofGetHeight(), animation*ofGetWidth()*1.3);

    // text
    ofRectangle shape;
    string s;
    if(animation<=0.15) ofSetColor(Colors[GAME_OBJ], (animation/0.15)*255);
    else ofSetColor(Colors[GAME_OBJ], 255-((animation-0.15)/0.85)*255);

    if(step<3){
        drawCenterText("Here, we need to do a little calibration:", ofGetWidth()/2, ofGetHeight()/2-fonts[MEDIUM].getLineHeight(), &fonts[MEDIUM]);
        drawCenterText("Place the ipad on the table", ofGetWidth()/2, ofGetHeight()/2, &fonts[MEDIUM]);
        drawCenterText("then touch the red circle", ofGetWidth()/2, ofGetHeight()/2+fonts[MEDIUM].getLineHeight()+15, &fonts[MEDIUM]);
    }
    
    else if(step<9){
        if(fg==0xffffff) s = "touch the white circle";
        else s = "now touch the black circle";
        shape = fonts[MEDIUM].getStringBoundingBox(s, ofGetWidth()/2, ofGetWidth()/2);
        fonts[MEDIUM].drawString(s, shape.x-shape.width/2, shape.y-shape.height/2-fonts[MEDIUM].getLineHeight());
    }
    else{
        s = "... etc";
        shape = fonts[MEDIUM].getStringBoundingBox(s, ofGetWidth()/2, ofGetWidth()/2);
        fonts[MEDIUM].drawString(s, shape.x-shape.width/2, shape.y-shape.height/2-fonts[MEDIUM].getLineHeight());
    }
}