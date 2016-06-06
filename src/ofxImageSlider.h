//
//  ofxImageSlider.h
//
//  Created by Alexey Rudenko on 3/26/13.
//
//

#include "ofMain.h"

class ofxImageSlider {
    
public:
    
    void setup();
    void setImgSize(int width, int height);
    void update();
    void draw();
    void draw(float x, float y);
    void calculateTarget();
    void slideTo(int target);
    
    
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
    
    void clear();
    int getCurrent();
    
private:
    
    float acceleration;
    float speed;
    float lastSpeed;
    int dx = 0;
    int lastX = 0;
    
    int itemWidth = 720 / 2;
    int itemHeight = 720 / 2;
};