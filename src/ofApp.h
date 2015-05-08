/*

problèmes:
     - avec 2 waves crées, le framerate est OK, mais à la 3e le framerate baisse sensiblement.
     - quand l'app est compilée en mode 'profile' avec l'outil core animations, le framerate
        est à 60 fps jusqu'à 6 waves. Il descend légèrement à la 7e mais revient à 60.
        À la 8e wave, le framerate descend et reste à ~30 fps
 
 */

#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

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
};


