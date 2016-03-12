#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
    ofGLESWindowSettings settings;
    settings.width = 1024;
    settings.height = 1024 - 22;
    settings.setGLESVersion(2);
    ofCreateWindow(settings);
    
    ofRunApp(new ofApp());
}
