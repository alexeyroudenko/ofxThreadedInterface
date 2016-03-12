//
//  ofxImageRotator.h
//
//  Created by Alexey Rudenko on 3/26/13.
//
//

#include "ofxImageRotator.h"

void ofxImageRotator::setup() {
    thumbMask.load("mask/thumb_mask.png");
    bigMask.load("mask/big_mask.png");
    loader.setup();
    loadShader();
}

void ofxImageRotator::loadShader() {
    string fileName = "shaders/gles/mask.frag";
#ifdef TARGET_OPENGLES
    ofLogWarning("[ofxImageRotator]", "[load] " + fileName);
    shader.load("shaders/gles/mask.vert", fileName);
#else
    fileName = "shaders/mask.frag";
    ofLogWarning("[ofxImageRotator]", "[load] " + fileName);
    shader.load("", fileName);
#endif
}

void ofxImageRotator::onReleased(string &message) {
    enableMouseEvents();
    currentDragged = -1;
}

void ofxImageRotator::onDragged(string &message) {
    disableMouseEvents();
    currentDragged = atoi(message.c_str());
}

void ofxImageRotator::clear() {
    loader.clean();
}

void ofxImageRotator::reload(string directory, int count) {
    countPhotoesOnRound = count;
    loader.load(directory);
}

void ofxImageRotator::update() {
    updateSlider();
}

int ofxImageRotator::getCenterX() {
    return ofGetWidth() / 2;
}

int ofxImageRotator::getCenterY() {
    return ofGetHeight() / 2;
}

void ofxImageRotator::draw(bool bshader, float size, float rotate, float radiusSmalles) {
    // when testing dont loading images (config: test_skip_unarchive)
    if (loader.loader->items.size() > 0) {
        ofEnableAlphaBlending();
        
        ofPushMatrix();
        ofPoint imageSize = ofPoint(loader.loader->items.at(current).getWidth(), loader.loader->items.at(current).getHeight());
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofScale(size, size);
        
        ofPushMatrix();
        ofTranslate(-imageSize.x / 2, -imageSize.y / 2);
        current = getCurrent();
        if (bshader == true) {
            shader.begin();
            shader.setUniformTexture("maskTex", bigMask.getTexture(), 1);
            loader.loader->items.at(current).draw(0, 0, imageSize.x, imageSize.y);
            shader.end();
        } else {
            loader.loader->items.at(current).draw(0, 0, imageSize.x, imageSize.y);
        }
        ofPopMatrix();
        
        drawThumbs(bshader, radiusSmalles);
        ofPopMatrix();
    }
    
    speed += rotate * 0.01;
}

void ofxImageRotator::drawThumbs(bool bshader, float radiusSmalles) {
    int j = 0;
    int i = 0;
    float oneElementSize = (loader.loader->thumbSize + PADDING);
    int radius = radiusSmalles * ofGetHeight() / 2.28;
    
    int count = loader.countToLoad; //loader.loader->thumbs.size();
    if (countPhotoesOnRound != -1) count = countPhotoesOnRound;
    
    for (int i = 0; i < loader.loader->thumbs.size(); i++) {
        alphas[i] += 0.09;
        alphas[i] = fmin(1.0, alphas[i]);
        alphas[i] = fmax(.0, alphas[i]);
        
        int positionX = i * oneElementSize - position;
        float percents = (positionX + 1.0 * loader.loader->thumbSize * count) / (1.0 * count * loader.loader->thumbSize);
        float angle = percents * 2.0 * PI + PI / 2;
        int coordX = radius * cos(angle);
        int coordY = radius * sin(angle);
        
        drawElement(&loader.loader->thumbs.at(i), coordX, coordY, alphas[i], bshader);
        
        ofSetHexColor(0xffffff);
    }
}

void ofxImageRotator::drawElement(ofImage *image, int coordX, int coordY, float alpha, bool bshader) {
    ofPushMatrix();
    ofTranslate(coordX, coordY);
    ofScale(alpha, alpha);
    
    if (bshader == true) {
        shader.begin();
        shader.setUniformTexture("maskTex", thumbMask.getTexture(), 1);
        shader.setUniform1f("alpha", alpha);
        image->draw(-loader.loader->thumbSize / 2, - loader.loader->thumbSize / 2);
        shader.end();
        
    } else {
        image->draw(-loader.loader->thumbSize / 2, - loader.loader->thumbSize / 2);
    }
    ofPopMatrix();
}


int ofxImageRotator::getCurrent() {
    if (loader.loader->items.size() == 0) return 0;
    return (int(round(position / (loader.loader->thumbSize + PADDING)))) % loader.loader->items.size();
}

int ofxImageRotator::getLength() {
    return (loader.loader->thumbSize + PADDING) * loader.loader->items.size();
}

void ofxImageRotator::updateSlider() {
    calculateTarget();
    if (loader.loader->items.size() == 0) {
        position = 0;
        return;
    }
    
    speed *= SPEED_FADE_OUT;
    position += speed;
    lastSpeed = speed;
    
    float length = (loader.loader->thumbSize + PADDING) * loader.loader->items.size();
    if (position < 0) position += getLength();
    if (position > length) position -= getLength();
    
}

void ofxImageRotator::calculateTarget() {
    if (loader.loader->items.size() == 0) {
        return;
    }
    current = getCurrent();
}





void ofxImageRotator::onMousePressed(ofMouseEventArgs& data) {
    ofLogVerbose("[ofxImageRotator]", "onMousePressed");
    isFree = false;
    listenDragg = true;
    lastAlpha = atan2(data.y - ofGetHeight() / 2, data.x - ofGetWidth() / 2) * 180.0 / PI;
}

void ofxImageRotator::onMouseDragged(ofMouseEventArgs& data) {
    if (listenDragg == true) {
        currentAlpha = atan2(data.y - ofGetHeight() / 2, data.x - ofGetWidth() / 2) * 180.0 / PI;
        dalpha = lastAlpha - currentAlpha;
        if (dalpha > 340) dalpha = 360.0 - dalpha;
        if (dalpha < -340) dalpha = 360.0 + dalpha;
        lastAlpha = currentAlpha;
        position += dalpha * 3.0;
        speed = 3.0 * dalpha / 1.0;
    }
}

void ofxImageRotator::onMouseReleased(ofMouseEventArgs& data) {
    isFree = true;
}


void ofxImageRotator::enable() {
    ofLogVerbose("[ofxImageRotator]", "enable " + ofToString(currentAlpha) + " " + ofToString(lastAlpha));
    enableMouseEvents();
    lastAlpha = currentAlpha;
    isFree = true;
    speed = 0;
    position = 0;
    listenDragg = false;
    isEnabled = true;
    for (int i = 0; i < 100; i++) alphas[i] = 0;
}

void ofxImageRotator::disable() {
    ofLogVerbose("[ofxImageRotator]", "disable " + ofToString(currentAlpha) + " " + ofToString(lastAlpha));
    disableMouseEvents();
    isFree = false;
    speed = 0;
    isEnabled = false;
}

void ofxImageRotator::enableMouseEvents() {
    ofAddListener(ofEvents().mousePressed, this, &ofxImageRotator::onMousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxImageRotator::onMouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &ofxImageRotator::onMouseReleased);
}

void ofxImageRotator::disableMouseEvents() {
    ofRemoveListener(ofEvents().mousePressed, this, &ofxImageRotator::onMousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxImageRotator::onMouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxImageRotator::onMouseReleased);
}