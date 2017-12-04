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
    edgeDetectCamera.initGrabber(320,240);
    highPassCamera.initGrabber(320,240);
    
    //Allocate pixels for the cameras
    myPixels1.allocate(grayScaleCamera.getWidth(), grayScaleCamera.getHeight(), 1);
    myPixels2.allocate(motionBlurCamera.getWidth(), motionBlurCamera.getHeight(), 1);
    myPixels3.allocate(edgeDetectCamera.getWidth(), edgeDetectCamera.getHeight(), 1);
    myPixels4.allocate(highPassCamera.getWidth(), highPassCamera.getHeight(), 1);

}

//--------------------------------------------------------------
void ofApp::update(){

    // ============ CAMERA 1: SIMPLE GREYSCALE ============
    grayScaleCamera.update();
    
    //If there is fresh data
    if (grayScaleCamera.isFrameNew()) {
        
        pix1 = grayScaleCamera.getPixels();

        //Loop through every pixel of the camera
        //Hard threshold the image and make it greyscale.
        for (int i =0; i < grayScaleCamera.getWidth()*grayScaleCamera.getHeight(); i += numChannels) {
            
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

    
    // ============ CAMERA 2: MOTION BLUR ============
    motionBlurCamera.update();

    if(motionBlurCamera.isFrameNew()) {

        pix2 = motionBlurCamera.getPixels();

        for(int i=0; i < motionBlurCamera.getWidth()*motionBlurCamera.getHeight(); i++) {

            myPixels2[i] = lastVals1[i%3] + blur * (pix2[i] - lastVals1[i%3]);
            
            lastVals1[i%3] = myPixels2[i];
        }
        
        motionBlurTexture.allocate(myPixels2);
    }
    

    /*
    // ============ CAMERA 3: EDGE DETECT ============
    edgeDetectCamera.update();

    if(edgeDetectCamera.isFrameNew()) {

        for(int i=0; i < edgeDetectCamera.getWidth()*edgeDetectCamera.getHeight(); i++) {

            myPixels3[i] = lastVals2[i%3] + edge * (pix3[i] - lastVals2[i%3]);

            lastVals2[i%3] = myPixels3[i];

            myPixels3[i] = pix3[i]-myPixels3[i];
        }

        edgeDetectTexture.allocate(myPixels3);
    }
    
    
    // ============ CAMERA 4: HIGH PASS (SHARPEN) ============
    highPassCamera.update();
    
    if(highPassCamera.isFrameNew()) {
        
        for(int i=0; i < highPassCamera.getWidth()*highPassCamera.getHeight(); i++) {
            
            myPixels4[i] = lastVals3[i%3] + blur * (pix4[i] - lastVals3[i%3]);
            
            lastVals3[i%3] = myPixels4[i];
            
            myPixels4[i] = pix4[i]-myPixels4[i];
        }
        
        highPassTexture.allocate(myPixels4);
    }
     */
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // Display 4 cameras
    grayscaleTexture.draw(20, 20);
    motionBlurTexture.draw(340,20);
//    edgeDetectTexture.draw(20, 340);
//    highPassTexture.draw(340, 340);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // Press space bar to take a snap!
    if (key == 32) {
        cout << "Picture taken!" << endl;
    }
    
    if(key == OF_KEY_UP) {
        numChannels++;
        cout << numChannels << endl;
        //prevent going too high (for performance reasons)
        if (numChannels >= 20) {
            numChannels = 20; //max numChannels is 21
        }
    }
    else if (key == OF_KEY_DOWN ) {
        numChannels--;
        cout << numChannels << endl;
        //cannot have less than 1 channel
        if (numChannels < 1) {
            numChannels = 1;
        }
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
