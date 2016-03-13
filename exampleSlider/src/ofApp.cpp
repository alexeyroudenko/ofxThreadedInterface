#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    slider.setup();
    loader.setup();
    loader.load("images/");
    
    slider.items = &loader.loader->items;
    slider.enableMouseEvents();
}

//--------------------------------------------------------------
void ofApp::update(){
    slider.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColorHex(0xf7f7f7);
    
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    slider.draw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
