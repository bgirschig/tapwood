#include "ofMain.h"
#include "ofApp.h"

int main(){
    ofAppiOSWindow* window = new ofAppiOSWindow();
    window->enableHardwareOrientation();
    window->enableRetina();
    
    ofSetupOpenGL(ofPtr<ofAppBaseWindow>(window), 1536, 2048, OF_FULLSCREEN);
    
    ofRunApp(new ofApp());
}
