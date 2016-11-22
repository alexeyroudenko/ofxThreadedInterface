#pragma once

//
//  ofxImageRotator.h
//
//  Created by Alexey Rudenko on 3/26/13.
//
//

#include "ofMain.h"
#include "ofxThreadedGalleryLoader.h"

#define SPEED_EDGE      0.02
#define SPEED_FADE_OUT  0.9
#define SHIFT_ANGLE     0
#define ICO_SIZE        0.5

#define PADDING 0

class ofxImageRotator {
    
public:
    
    ofParameter<float> bgRadius = 0.2;
    ofParameter<float> bgAlpha = 0.2;
    
    ofxThreadGalleryLoader loader;
    
    ofShader shader;
    ofImage thumbMask;
    ofImage bigMask;
    
    ofEvent<string> onPhotoSelect;
    
    float smallRoundScale = 1.0;
    
    void setup(int imageSize = 512, int thumbSize = 128);
    void loadShader();
    void onReleased(string &message);
    void onDragged(string &message);
    void clear();
    void reload(string directory, int count = -1);
    void update();
    
    //bool bshader, float size = 1.0, float rotate = 0.0, float radiusSmalles = 1.0
    void draw(bool bshader, float size = 1.0, float rotate = 0.0, float radiusSmalles = 1.0);
    void draw();
    
    void updateMaskSize();
    
    int getCurrent();
    int getLength();
    int getCenterX();
    int getCenterY();
    
    void updateSlider();
    
    void moveTo(int index);
    float   position = 0;
    
    void calculateTarget();

    void enable();
    void disable();

    void enableMouseEvents();
    void disableMouseEvents();

    void onMousePressed(ofMouseEventArgs& data);
    void onMouseDragged(ofMouseEventArgs& data);
    void onMouseReleased(ofMouseEventArgs& data);
    void windowResized(ofResizeEventArgs &args);

    float positionX = 0;
    float positionY = 0;
    
    
    bool bshader = true;
    float size = 1.0;
    double autoRotateSpeed = 0.0;
    float radiusSmalles = 1;
    
    double moveSpeed = 1.0;

private:
    
    unsigned int    current = 0;
    int previousIndex = -1;
    float lastAlpha;
    float currentAlpha = 0;
    float   dalpha = 0;
    double   speed = 0.0;
    double   lastSpeed = 0;
    float   acceleration = 0.99;
    bool    isFree = true;
    
    int currentDragged = -1;
    bool isEnabled = true;
    bool listenDragg = false;
    int countPhotoesOnRound = 16;
    float alphas[100];
    float lastScale = 1.0;
    
    void drawThumbs(bool bshader, float radiusSmalles);
    void drawElement(ofImage *image, int coordX, int coordY, float alpha, bool bshader);
    
    int width;
    int height;

};
