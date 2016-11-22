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


void ofxImageSlider::setup() {
    items = new std::vector<ofImage>();
    currentIndex = 0;
    currentCoord = 0;
    targetCoord = 0;
    speed = 0.0;
    acceleration = 0.99;
    padding = 10;
    isFree = true;
    
}

void ofxImageSlider::setImgSize(int width, int height) {
    itemWidth = width;
    itemHeight = height;
}


void ofxImageSlider::slideTo(int target, bool fast) {
    ofLogVerbose("ofxImageSlider", "slide to " + ofToString(target));
    targetIndex = target;
    targetCoord = target * (itemWidth + padding);

    if (fast) {
        currentIndex = target;
        currentCoord = target * (itemWidth + padding);
    }
}

void ofxImageSlider::update() {
    
    if (items->size() == 0) {
        currentCoord = 0;
        return;
    }
    
    if (isFree == true) {
        float fg = -0.007 * (currentCoord - targetCoord);
        speed += fg;
    }
    
    speed *= SPEED_FADE_OUT;
    currentCoord += speed;
    lastSpeed = speed;
    string fileName = ofToString(currentIndex);
    if (currentIndex != previousIndex) ofNotifyEvent(onPhotoSelect, fileName);
    previousIndex = currentIndex;
}

int ofxImageSlider::getCurrent() {
    if (items->size() == 0) return 0;
    int current = (int(round(currentCoord / (itemWidth + padding)))) % items->size();
    return current;
}

void ofxImageSlider::previous() {
    ofLogVerbose("ofxImageSlider", "previous");
    if (targetIndex > 0) {
        slideTo(targetIndex - 1, false);
    }
}

void ofxImageSlider::next() {
    ofLogVerbose("ofxImageSlider", "next from target " + ofToString(targetIndex));
    if (targetIndex < items->size() - 1) {
        slideTo(targetIndex + 1, false);
    }
}

string ofxImageSlider::debugString() {
    stringstream info;
    info << " currentIndex:" + ofToString(currentIndex) + " currentCoord:" + ofToString(currentCoord) + "\n";
    info << " targetIndex:" + ofToString(targetIndex) + " targetCoord:" + ofToString(targetCoord) + "\n";
    info << " count:" + ofToString(items->size()) + "\n";
    info << " lastX:" + ofToString(lastX,0) + " dx:" + ofToString(dx,0) + " speed:" + ofToString(speed, 2);
    return info.str();
}

void ofxImageSlider::drawDebug() {
    ofDrawBitmapStringHighlight(debugString(), 40, ofGetHeight() - 60);
}

void ofxImageSlider::clear() {
    items->clear();
    items = new std::vector<ofImage>();
}

void ofxImageSlider::draw() {
    float oneElementSize = (itemWidth + padding);
    for (int i = 0; i < items->size(); i++) {
        int positionX = i * oneElementSize - currentCoord;
        float size = 1 / (positionX * positionX / 200000.0 + 1);
        int width = itemWidth * size;
        int height = itemHeight * size;
        items->at(i).draw(i * oneElementSize - currentCoord - width / 2, - height / 2, width, height);
    }
}

void ofxImageSlider::enableMouseEvents() {
    ofAddListener(ofEvents().mousePressed, this, &ofxImageSlider::onMousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxImageSlider::onMouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &ofxImageSlider::onMouseReleased);
    lastX = 0;
}

void ofxImageSlider::disableMouseEvents() {
    ofRemoveListener(ofEvents().mousePressed, this, &ofxImageSlider::onMousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxImageSlider::onMouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxImageSlider::onMouseReleased);
}

void ofxImageSlider::onMousePressed(ofMouseEventArgs& data) {
    if (data.y < maxY) {
        isFree = false;
        lastX = data.x;
    }
}

void ofxImageSlider::onMouseDragged(ofMouseEventArgs& data) {
    if (data.y <maxY) {
        if (lastX && data.y < maxY) {
            dx = lastX - data.x;
        }
        
        lastX = data.x;
        
        int max = (items->size() - 1) * (itemWidth + padding);
        if (currentCoord < 0 && dx < 0) {
            dx = dx / (-currentCoord * 0.3 + 1.0);
        }
        
        if (currentCoord > max && dx > 0) {
            dx = dx / ((currentCoord - max) * 0.3 + 1.0);
        }

        if (lastX) {
            currentCoord += dx / 2.0;
        }
        
        speed = dx / 2.0;
        
        currentIndex = getCurrent();
        targetIndex = currentIndex;
        targetCoord = targetIndex * (itemWidth + padding);
    }
}

void ofxImageSlider::onMouseReleased(ofMouseEventArgs& data) {
    if (data.y < maxY)
    isFree = true;
}