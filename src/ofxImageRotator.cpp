//
//  ofxImageRotator.h
//
//  Created by Alexey Rudenko on 3/26/13.
//
//

#include "ofxImageRotator.h"

void ofxImageRotator::setup(int imageSize, int thumbSize) {
    
    thumbMask.load("mask/thumb_mask.png");
    bigMask.load("mask/big_mask.png");
    
    loader.setup();
    loader.setSize(imageSize, thumbSize, true);
    //loader.loader->imageSize = imageSize;
    //loader.loader->thumbSize = thumbSize;
    loadShader();
    
    width = ofGetWidth();
    height = ofGetHeight();
    ofAddListener(ofEvents().windowResized, this, &ofxImageRotator::windowResized);
}

void ofxImageRotator::windowResized(ofResizeEventArgs &args) {
    width = args.width;
    height = args.height;
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

void ofxImageRotator::updateMaskSize() {
    bigMask.resize(loader.loader->imageSize, loader.loader->imageSize);
    thumbMask.resize(loader.loader->thumbSize, loader.loader->thumbSize);
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
    current = 0;
    loader.clean();
}

void ofxImageRotator::reload(string directory, int count) {

    int countLoading = loader.load(directory);
    if (count == -1) {
        count = countLoading;
    }
    countPhotoesOnRound = count;
}

void ofxImageRotator::update() {
    updateSlider();
}

int ofxImageRotator::getCenterX() {
    return width / 2;
}

int ofxImageRotator::getCenterY() {
    return height / 2;
}

void ofxImageRotator::draw(bool bshader_, float size_, float rotate_, float radiusSmalles_) {
    bshader = bshader_;
    size = size_;
    rotate = rotate_;
    radiusSmalles = radiusSmalles_;
    draw();
}

void ofxImageRotator::draw() {
    
    // when testing dont loading images (config: test_skip_unarchive)
    if (loader.loader->items.size() > 0) {
        ofEnableAlphaBlending();
        
        ofPushMatrix();
        ofPoint imageSize = ofPoint(loader.loader->items.at(current).getWidth(), loader.loader->items.at(current).getHeight());
        ofTranslate(width / 2 + positionX, height / 2 + positionY);
        ofScale(size, size);

        ofSetCircleResolution(64);
        ofSetColor(255, 255 * bgAlpha);
        ofDrawCircle(0, 0, imageSize.x * bgRadius);
        ofSetColor(255);

        
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
    lastScale = size;
    speed += rotate * 0.1;
}


void ofxImageRotator::drawThumbs(bool bshader, float radiusSmalles) {
    int j = 0;
    int i = 0;
    float oneElementSize = (loader.loader->thumbSize + PADDING);
    int radius = radiusSmalles * (loader.loader->imageSize - loader.loader->thumbSize);
    int count = loader.countToLoad;
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
    string fileName = ofToString(current);
    if (current != previousIndex) ofNotifyEvent(onPhotoSelect, fileName);
    previousIndex = current;
}

void ofxImageRotator::moveTo(int index) {
    ofLogVerbose("ofxImageRotator", "move " + ofToString(current) + ">" + ofToString(index));
    speed+=4;
    if (current > index) speed-=4;
    current = index;
}

void ofxImageRotator::calculateTarget() {
    if (loader.loader->items.size() == 0) {
        return;
    }
    current = getCurrent();
}


/* --------------------------------------------------------------
 # Mouse
 #
 #
 #
 # -------------------------------------------------------------- */
void ofxImageRotator::onMousePressed(ofMouseEventArgs& data) {
    ofVec2f d = ofVec2f(data.x - width / 2 - positionX, data.y - height / 2 - positionY);
    if (d.length() < loader.loader->imageSize * lastScale * 1) {
        //ofLogVerbose("" + ofToString(d.length()) + "<" + ofToString(loader.loader->imageSize) + "*" + ofToString(lastScale));
        isFree = false;
        listenDragg = true;
        lastAlpha = atan2(data.y - height / 2 - positionY, data.x - width / 2 - positionX) * 180.0 / PI;
    }
}

void ofxImageRotator::onMouseDragged(ofMouseEventArgs& data) {
    if (listenDragg == true) {
        ofVec2f d = ofVec2f(data.x - width / 2 - positionX, data.y - height / 2 - positionY);
        if (d.length() < loader.loader->imageSize * lastScale * 1) {
            currentAlpha = atan2(data.y - height / 2 - positionY, data.x - width / 2 - positionX) * 180.0 / PI;
            dalpha = lastAlpha - currentAlpha;
            if (dalpha > 340) dalpha = 360.0 - dalpha;
            if (dalpha < -340) dalpha = 360.0 + dalpha;
            lastAlpha = currentAlpha;
            position += dalpha * moveSpeed;
            speed = 2.0 * moveSpeed * dalpha / 1.0;
        }
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
