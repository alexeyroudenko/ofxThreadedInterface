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
    bool scaling = false;
    
    ofShader shader;
    ofImage thumbMask;
    ofImage bigMask;
    
    int currentDragged = -1;
    bool isEnabled = true;
    bool listenDragg = false;
    int countPhotoesOnRound = 16;
    float alphas[100];
    
    unsigned int    current = 0;
    float lastAlpha;
    float currentAlpha = 0;
    float   dalpha = 0;
    float   speed = 0.0;
    float   lastSpeed = 0;
    float   acceleration = 0.99;
    float   position = 0;
    bool    isFree = true;
    
    ofxThreadGalleryLoader loader;
    
    float smallRoundScale = 1.0;
    
    void setup();
    void loadShader();
    void onReleased(string &message);
    void onDragged(string &message);
    void clear();
    void reload(string directory, int count = 24);
    void update();
    void draw(bool bshader, float size = 1.0, float rotate = 0.0, float radiusSmalles = 1.0);
    void drawThumbs(bool bshader, float radiusSmalles);
    void drawElement(ofImage *image, int coordX, int coordY, float alpha, bool bshader);
    
    int getCurrent();
    int getLength();
    int getCenterX();
    int getCenterY();
    
    void updateSlider();
    void calculateTarget();

    void enable();
    void disable();

    void enableMouseEvents();
    void disableMouseEvents();

    void onMousePressed(ofMouseEventArgs& data);
    void onMouseDragged(ofMouseEventArgs& data);
    void onMouseReleased(ofMouseEventArgs& data);
};