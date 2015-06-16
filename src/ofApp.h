/*
flags:
    FIXME: ...
    OPTIM: ...
    TODO: ...
*/

#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "connection.h"
#include "PointElement.h"
#include "Game.h"
#include "errno.h"
#include "Calibrator.h"
#include "Utils.h"
#include "ofxAccelerometer.h"

class ofApp : public ofxiOSApp {
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
        // events
        void initEvents();
        void onServerEvent(string & e);
        void onDeviceEvent(string & e);
        void onDataEvent(string & e);
        void onPlaySoundEvent(string & e);
    
        void onTapEvent(ofVec2f & e);
        void onButton(ButtonKind & kind);
    
        // main elements
        Calibrator cal;
        Game game;
        connection serverConnection;
    
        // utils
        ofVec2f testPos;
        ofTrueTypeFont fonts[3];
        ofSoundPlayer tapSounds[5];
        ofSoundPlayer validSounds[3];
        ofSoundPlayer wrongSounds[3];
        ofSoundPlayer upSounds[3];
    
        //settings
        bool connect;
        bool serverInterface;
        bool debug;
        bool touchDebug;
};


