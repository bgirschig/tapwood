/*
 currentState: max 26 simultaneous waves
 pb: mesh's drawVertices() does not seem to be able to draw more than 1px -> too small
*/

#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "connection.h"
#include "Obstacle.h"

#include "Wave.h"

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
    
        // preso vars
        vector<Wave> waves;
        Obstacle test;
    
        // events
        void onServerEvent(string & e);
        void onDeviceEvent(string & e);
        void onDataEvent(string & e);
        connection serverConnection;
};


