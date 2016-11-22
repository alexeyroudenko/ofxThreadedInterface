#pragma once

#include "ofMain.h"
#include "ofxImageSlider.h"
#include "ofxThreadedGalleryLoader.h"

class ofxSliderAdapter {
    
public:
    
    ofxImageSlider slider;
    ofxThreadGalleryLoader loader;
    
    void setup(int width = 1920, int height = 1080, float scale = 0.4) {
        
        ofPoint size(width, height);

        slider.setup();
        slider.setImgSize(size.x * scale, size.y * scale);
        slider.padding = -200;
        
        loader.setup();
        loader.setSize(size.x * scale, size.y * scale, false);
        slider.items = &loader.loader->items;
    }
    
    void update() {
        slider.update();
    }
};
