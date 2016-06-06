//
//  ofxImageSlider.cpp
//
//  Created by Alexey Rudenko on 3/26/13.
//
//

#include "ofxImageSlider.h"
#include "ofMain.h"

#define COUNT 12
#define SPEED_EDGE 0.02
#define SPEED_FADE_OUT 0.9
#define SHIFT_ANGLE 0
#define ICO_SIZE 0.5
#define PADDING 10

//#define WIDTH 720 / 2
//#define HEIGHT 720 / 2

void ofxImageSlider::setup() {
    items = new std::vector<ofImage>();
    position = 0;
    destination = 0;
    speed = 0.0;
    acceleration = 0.99;
    current = 0;
}

void ofxImageSlider::setImgSize(int width, int height) {
    itemWidth = width;
    itemHeight = height;
}

void ofxImageSlider::update() {
    calculateTarget();
    if (items->size() == 0) {
        position = 0;
        return;
    }
    
//    int max = (items->size() - 1)* (WIDTH + PADDING);
//    position = fmax(position, 0);
//    position = fmin(max, position);
    
    if (isFree == true && fabs(speed) < SPEED_EDGE) {
        position -= (1.0 * position - destination) / 25.0;
    }
    
    if (isFree == true) {
        int max = (items->size() - 1) * (itemWidth + PADDING);
        if (position < 0 && dx < 0) {
            speed = speed / (-position * 0.5 + 1.0);
        }
        
        if (position > max && dx > 0) {
            speed = speed / ((position - max) * 0.5 + 1.0);
        }
    }
    
    speed *= SPEED_FADE_OUT;
    position += speed;
    lastSpeed = speed;
}

int ofxImageSlider::getCurrent() {
    return (int(round(position / (itemWidth + PADDING)))) % items->size();
}

void ofxImageSlider::calculateTarget() {
    if (items->size() == 0) {
        destination = 0;
        return;
    }
    
    float value = position / (itemWidth + PADDING);
    int intValue = floor(position / (itemWidth + PADDING));
    
    float delta = value - intValue;
    
    if (delta < 0.5) {
        destination = intValue * (itemWidth + PADDING);
    } else {
        destination = (intValue + 1) * (itemWidth + PADDING);
    }
    
    current = getCurrent();
}

void ofxImageSlider::slideTo(int target) {
    position = target * (itemWidth + PADDING);
    current = target;
}

void ofxImageSlider::clear() {
    items->clear();
    items = new std::vector<ofImage>();
}

void ofxImageSlider::draw() {
    float oneElementSize = (itemWidth + PADDING);
    for (int i = 0; i < items->size(); i++) {
        int positionX = i * oneElementSize - position;
        float size = 1 / (positionX * positionX / 200000.0 + 1);
        int width = itemWidth * size;
        int height = itemHeight * size;
        
//        items->at(i).draw(i * oneElementSize - position - WIDTH / 2, - HEIGHT / 2, WIDTH, HEIGHT);
        items->at(i).draw(i * oneElementSize - position - width / 2, - height / 2, width, height);
    }
}

void ofxImageSlider::enableMouseEvents() {
    ofAddListener(ofEvents().mousePressed, this, &ofxImageSlider::onMousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxImageSlider::onMouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &ofxImageSlider::onMouseReleased);
}

void ofxImageSlider::disableMouseEvents() {
    ofRemoveListener(ofEvents().mousePressed, this, &ofxImageSlider::onMousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxImageSlider::onMouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxImageSlider::onMouseReleased);
}

void ofxImageSlider::onMousePressed(ofMouseEventArgs& data) {
    
    if (data.y < 650) {
        isFree = false;
        lastX = data.x;
    }
}

void ofxImageSlider::onMouseDragged(ofMouseEventArgs& data) {
    if (data.y < 650) {
        if (lastX && data.y < 650) {
            dx = lastX - data.x;
        }
        
        lastX = data.x;
        
        int max = (items->size() - 1) * (itemWidth + PADDING);
        if (position < 0 && dx < 0) {
            dx = dx / (-position * 0.3 + 1.0);
        }
        
        if (position > max && dx > 0) {
            dx = dx / ((position - max) * 0.3 + 1.0);
        }

        if (lastX ) {
            position += dx / 1.0;
        }
        
        speed = dx / 1.0;
    }
}

void ofxImageSlider::onMouseReleased(ofMouseEventArgs& data) {
    if (data.y < 650)
    isFree = true;
}