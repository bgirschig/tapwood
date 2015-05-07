#include "ofMain.h"
#include "ofApp.h"

int main(){
//    openframeworks - retina Ipad FIX
    ofAppiOSWindow* window = new ofAppiOSWindow();
    window->enableHardwareOrientation();
    window->enableRetina();
    
    ofSetupOpenGL(ofPtr<ofAppBaseWindow>(window), 1536, 2048, OF_FULLSCREEN);

//    original
//    ofSetupOpenGL(1024,768,OF_FULLSCREEN);			// <-------- setup the GL context
	
    
    ofRunApp(new ofApp());
}
