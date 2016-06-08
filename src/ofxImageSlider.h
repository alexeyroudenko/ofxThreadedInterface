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
    void slideTo(int target, bool fast = true);
    
    void drawDebug();
    
    std::vector<ofImage> *items;
    
    void enableMouseEvents();
    void disableMouseEvents();
    void onMousePressed(ofMouseEventArgs& data);
    void onMouseDragged(ofMouseEventArgs& data);
    void onMouseReleased(ofMouseEventArgs& data);
    
    void clear();
    int getCurrent();
    
    float padding;
    
    void previous();
    void next();
    
private:
    
    unsigned int currentIndex = 0;
    unsigned int targetIndex = 0;
    
    float currentCoord;
    float targetCoord;

    bool isFree;
    
    float acceleration;
    float speed;
    float lastSpeed;
    int dx = 0;
    int lastX = 0;
    
    int itemWidth = 720 / 2;
    int itemHeight = 720 / 2;
};