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
    grayScaleCamera.initGrabber(320,240);
    motionBlurCamera.initGrabber(320,240);
    myCamera3.initGrabber(320,240);
    myCamera4.initGrabber(320,240);
    
    //Allocate pixels for the cameras
    myPixels1.allocate(grayScaleCamera.getWidth(), grayScaleCamera.getHeight(), 1);
    myPixels2.allocate(motionBlurCamera.getWidth(), motionBlurCamera.getHeight(), 1);


}

//--------------------------------------------------------------
void ofApp::update(){

    // CAMERA 1: SIMPLE GREYSCALE
    grayScaleCamera.update();
    
    //If there is fresh data
    if (grayScaleCamera.isFrameNew()) {
        
        pix1 = grayScaleCamera.getPixels();

        //Loop through every pixel of the camera
        //Hard threshold the image and make it greyscale.
        for (int i =0; i < grayScaleCamera.getWidth()*grayScaleCamera.getHeight(); i++) {
            
            int index = i*3;
            
            // 0.2126*R + 0.7152*G + 0.0722*B
            myPixels1[i]=(pix1[index] * 0.2126) + (pix1[index+1] * 0.7152) + (pix1[index+2] * 0.0722);
            
            if (myPixels1[i] > 128)
                myPixels1[i]=255;
            else
                myPixels1[i]=0;
        }
        grayscaleTexture.allocate(myPixels1);
    }

    // CAMERA 2: MOTION BLUR
    motionBlurCamera.update();

    if(motionBlurCamera.isFrameNew()) {

        pix2 = motionBlurCamera.getPixels();

        for(int i=0; i < motionBlurCamera.getWidth()*motionBlurCamera.getHeight(); i++) {
            
            myPixels2[i] = lastVals[i%3] + blur * (pix2[i] - lastVals[i%3]);
            
            lastVals[i%3] = myPixels2[i];
        }
        
        motionBlurTexture.allocate(myPixels2);
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // Display 4 cameras
    grayscaleTexture.draw(20, 20);
    motionBlurTexture.draw(340,20);
    
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
