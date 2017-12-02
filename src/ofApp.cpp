#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Project 4: Photobooth
 
 by Uyen Le
 tle004@gold.ac.uk
 29/11/2017 - 1/12/2017
 
 ----------------
 A simple project that explores live camera capture and video processing to create a photobooth.
 
 ----------------
 Credits:

 */

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Allocate memory for the cameras
    myCamera1.initGrabber(320,240);
    myCamera2.initGrabber(320,240);
    myCamera3.initGrabber(320,240);
    myCamera4.initGrabber(320,240);
    
    pixels.allocate(640,480,3);
    pixels2.allocate(640,480,3);
    
//    pixelout.allocate(320, 240, 1);
//    lastPixels.allocate(320,240,3);
}

//--------------------------------------------------------------
void ofApp::update(){

    myCamera1.update();
    
    pixels = myCamera1.getPixels();
    
    // CAMERA 1: Background subtraction
    for (int i = 0 ; i < pixels.size() ; i++) {
        
        pixels[i] = abs(pixels[i]-pixels2[i]);
    }
    
    backgroundSubtraction.allocate(pixels);
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // Display 4 camerasofTexture myTexture;
    backgroundSubtraction.draw(0,0);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // Press space bar to take a snap!
    if (key == 32) {
        pixels2 = myCamera1.getPixels();
        cout << "Picture taken!" << endl;
    }
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
