#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Project 4: Photobooth
 
 by Uyen Le
 tle004@gold.ac.uk
 29/11/2017 - 1/12/2017
 
 ----------------
 A simple project that explores live camera pixels processing to create a photobooth.
 
 ----------------
 Credits:
 - Background subtraction tutorial: http://openframeworks.cc/ofBook/chapters/image_processing_computer_vision.html#acompleteworkflowbackgroundsubtraction
 */

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    //Allocate memory for the cameras
    myCamera1.initGrabber(320,240);
    myCamera2.initGrabber(320,240);
    myCamera3.initGrabber(320,240);
    myCamera4.initGrabber(320,240);
    
    myPixels.allocate(myCamera1.getWidth(), myCamera1.getHeight(), 1);
    
//    pix = myCamera1.getPixels();

}

//--------------------------------------------------------------
void ofApp::update(){

    // CAMERA 1: SIMPLE GREYSCALE
    myCamera1.update();
    
    //If there is fresh data
    if (myCamera1.isFrameNew()) {
        
        pix = myCamera1.getPixels();

        //Loop through every pixel of the camera
        //Hard threshold the image and make it greyscale.
        for (int i =0;i<myCamera1.getWidth()*myCamera1.getHeight();i++) {
            
            int index = i*3;
            
            // 0.2126*R + 0.7152*G + 0.0722*B
            myPixels[i]=(pix[index] * 0.2126) + (pix[index+1] * 0.7152) + (pix[index+2] * 0.0722);
            
            if (myPixels[i] > 128)
                myPixels[i]=255;
            else
                myPixels[i]=0;
        }
        myTexture1.allocate(myPixels);
    }


}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // Display 4 cameras
    myTexture1.draw(20, 20);
    
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
