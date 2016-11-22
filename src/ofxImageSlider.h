#pragma once
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
    //void draw(float x, float y);
    void slideTo(int target, bool fast = true);
    
    void drawDebug();
    string debugString();
    
    std::vector<ofImage> *items;
    
    void enableMouseEvents();
    void disableMouseEvents();
    void onMousePressed(ofMouseEventArgs& data);
    void onMouseDragged(ofMouseEventArgs& data);
    void onMouseReleased(ofMouseEventArgs& data);
    
    void clear();
    
    int getCurrent();
    int getPrevious();
    
    float padding;
    float maxY = 650;
    void previous();
    void next();
    
    
    ofEvent<string> onPhotoSelect;
    
    
private:
    
    int previousIndex = -1;
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
