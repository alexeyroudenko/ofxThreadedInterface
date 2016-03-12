#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    rotator.setup();
    rotator.loader.loader->thumbSize = 128;
    rotator.loader.loader->imageSize = 512;
    
    rotator.reload("images", 10);
    rotator.enable();
}

//--------------------------------------------------------------
void ofApp::update(){
    rotator.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(128);
    
    float roationSpeed = 12.0;
    rotator.draw(true, 1.0, roationSpeed, 1.0);
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
