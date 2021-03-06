#pragma once

#include "ofMain.h"
#include "ofxImageRotator.h"

class ofRotatorAdapter {
private:
    

public:
    
    /* --------------------------------------------------------------
     # Rotator
     #
     # -------------------------------------------------------------- */
    ofxImageRotator rotator;
    ofParameterGroup settings;
    ofParameter<float>   verticalPosition;
    ofParameter<float>   smallRadius;
    ofParameter<float>   bigRadius;
    ofParameter<float>   interfaceX;
    ofParameter<float>   interfaceY;
    ofParameter<float>   interfaceR;
    ofParameter<float>   waitFrames;
    ofParameter<bool>   doRotate;
    ofParameter<bool>   doAutoSwitch;
    ofParameter<bool>   doSwitchExamples;
    ofParameter<float>   autoSwitchFrames;
    
    ofParameter<float>   panelX;
    ofParameter<float>   panelY;
    
    void setup() {
        settings.setName("Rotator");
        settings.add(smallRadius.set("smallRadius", 0.5, 0., 1.));
        settings.add(bigRadius.set("bigRadius", 0.5, 0., 1.));
        settings.add(rotator.bgRadius.set("bgRadius", 0.5, 0., 1.));
        settings.add(rotator.bgAlpha.set("bgAlpha", 0.5, 0., 1.));
        settings.add(interfaceX.set("interfaceX", 0.1, -0.5, .5));
        settings.add(interfaceY.set("interfaceY", 0.1, -0.5, .5));
        settings.add(waitFrames.set("waitFrames", 10., 0., 200.));
        settings.add(doRotate.set("doRotate", true));
        settings.add(interfaceR.set("autoRotate", 0.1, -2, 2));
        
        settings.add(panelX.set("panelX", 0.1, 0.0, 1.0));
        settings.add(panelY.set("panelY", 0.1, 0.0, 1.0));
        
        rotator.setup();
    }
    
    void draw() {
        rotator.draw();
    }

    void onSelectFace(string &indexString) {
        ofLogVerbose("ofRotatorAdapter", "onSelectFace " + indexString);
    }
    
    void update(int width, int height) {
        rotator.positionX = interfaceX * width;
        rotator.positionY = interfaceY * height;
        float angle = interfaceR * (doRotate == true ? 1.0 : 0.0);
        rotator.bshader = true;
        rotator.size = smallRadius;
        rotator.autoRotateSpeed = angle;
        rotator.radiusSmalles = bigRadius;
        rotator.moveSpeed = 0.6;
        rotator.update();
    }
};
