//
//  ofxPhotoSlider.h
//
//  Created by Alexey Rudenko on 3/26/13.
//
//

#include "ofMain.h"
#include "ofMain.h"

class ofxImageSlider {
    
public:
    
    void setup();
    void update();
    void draw();
    void draw(float x, float y);
    
    void calculateTarget();
    void slideTo(int target);
    
    float acceleration;
    float speed;
    float lastSpeed;
    
    unsigned int    current;
    float           position;
    float           destination;
    bool            isFree;
    
    std::vector<ofImage> *items;
    
    void enableMouseEvents();
    void disableMouseEvents();
    void onMousePressed(ofMouseEventArgs& data);
    void onMouseDragged(ofMouseEventArgs& data);
    void onMouseReleased(ofMouseEventArgs& data);
    
    int dx = 0;
    int lastX = 0;
    
    void clear();
    int getCurrent();
};