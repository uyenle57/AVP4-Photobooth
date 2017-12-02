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
    
    myPixels.allocate(640,480,3);
    pixels.allocate(640,480,3);
    pixels2.allocate(640,480,3);
    
//    pixelout.allocate(320, 240, 1);
//    lastPixels.allocate(320,240,3);
}

//--------------------------------------------------------------
void ofApp::update(){

    // CAMERA 1: SIMPLE GREYSCALE
    myCamera1.update();
    
    if (myCamera1.isFrameNew()) {
        
        myPixels = myCamera1.getPixels();
        
        //Loop through every pixel of the camera
        for(int i=0; i < 320; i++) {
            for(int j=0; j < 240; j++) {
                
                //get the current pixel position
                int index = (i+j)*3;
                
                //update the RBG values of each pixel
                // 0.2126*R + 0.7152*G + 0.0722*B
                float red = (pixels[index] * 0.2126);
                float green = (pixels[index+1] * 0.7152);
                float blue = (pixels[index+2] * 0.0722);
                
                myPixels[i] = red + green + blue;
                
                //If current pixel is larger than threshold value of 128
                if (myPixels[i] > 128)
                    myPixels[i] = 255; //set pixel colour to white
                else
                    myPixels[i]=0; //otherwise set it to black if below threshold value
            }
        }
    }
    
    myTexture1.allocate(myPixels);
    

    // CAMERA 2
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // Display 4 camerasofTexture myTexture;
    myTexture1.draw(0,0);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // Press space bar to take a snap!
    if (key == 32) {
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
