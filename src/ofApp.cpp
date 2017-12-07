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
 -
 */

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    
    //Allocate memory for the cameras
    grayScaleCamera.initGrabber(320,240);
    motionBlurCamera.initGrabber(320,240);
    frameDiffCamera.initGrabber(320,240);
    highPassCamera.initGrabber(320,240);
    
    //Allocate pixels for the cameras
    myPixels1.allocate(grayScaleCamera.getWidth(), grayScaleCamera.getHeight(), 1);
    myPixels2.allocate(motionBlurCamera.getWidth(), motionBlurCamera.getHeight(), numChannel);
    myPixels4.allocate(highPassCamera.getWidth(), highPassCamera.getHeight(), numChannel);
    myPixels3.allocate(frameDiffCamera.getWidth(), frameDiffCamera.getHeight(), 1);
    lastPixels.allocate(frameDiffCamera.getWidth(), frameDiffCamera.getHeight(), numChannel);

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
        for (int i =0; i < grayScaleCamera.getWidth()*grayScaleCamera.getHeight(); i += grayscaleChannel) {
            
            int index = i*3;
            
            // 0.2126*R + 0.7152*G + 0.0722*B
            myPixels1[i]=(pix1[index] * 0.2126) + (pix1[index+1] * 0.7152) + (pix1[index+2] * 0.0722);
            
            //Set the threshold level
            if (myPixels1[i] > 128)
                myPixels1[i]=255; //set to white
            else
                myPixels1[i]=0; //else set to black
        }
        grayscaleTexture.allocate(myPixels1);
    }


    // ============ CAMERA 2: MOTION BLUR ============
    motionBlurCamera.update();

    if(motionBlurCamera.isFrameNew()) {

        pix2 = motionBlurCamera.getPixels();

        for(int i=0; i < motionBlurCamera.getWidth()*motionBlurCamera.getHeight()*numChannel; i++) {

            myPixels2[i] = lastVals1[i%3] + blur * (pix2[i] - lastVals1[i%3]);
            
            lastVals1[i%3] = myPixels2[i];
        }
        
        motionBlurTexture.allocate(myPixels2);
    }


    // ============ CAMERA 3: FRAME DIFFERENCING ============
    frameDiffCamera.update();

    if(frameDiffCamera.isFrameNew()) {
        
        pix3 = frameDiffCamera.getPixels();

        for (int i = 0; i < 320; i++){
            for (int j = 0; j < 240; j++) {
                
                //Frame Difference on the red channel
                myPixels3[(j*320+i)]=abs((lastPixels[(j*320+i)*3])-(pix3[(j*320+i)*3]));
                
                lastPixels[(j*320+i)*3]=pix3[(j*320+i)*3];
            }
        }
        
        frameDiffTexture.allocate(myPixels3);

    }

    // ============ CAMERA 4: HIGH PASS (SHARPEN) ============
    highPassCamera.update();
    
    if(highPassCamera.isFrameNew()) {
 
        pix4 = highPassCamera.getPixels();
 
        for(int i=0; i < highPassCamera.getWidth()*highPassCamera.getHeight()*numChannel; i++) {

            myPixels4[i] = lastVals3[i%3] + blur * (pix4[i] - lastVals3[i%3]);

            lastVals3[i%3] = myPixels4[i];

            myPixels4[i] = pix4[i]-myPixels4[i];
        }

        highPassTexture.allocate(myPixels4);
        
    }

    ////////

}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // Display 4 cameras
    grayscaleTexture.draw(20, 20);
    motionBlurTexture.draw(360,20);
    highPassTexture.draw(20, 280);
    frameDiffTexture.draw(360, 280);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // Press space bar to take a photo!
    if (key == 32) {
        snapshot.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        snapshot.save("screenshot.png");
        cout << "Picture taken!" << endl;
    }
    
    if(key == OF_KEY_UP) {
        grayscaleChannel++;
        blur++;
        
        cout << "grayscaleChannel: " << grayscaleChannel << endl;
        cout << "blur " << blur << endl;
        
        //prevent values too high
        //otherwise the effects wil be screwed up
        if (grayscaleChannel >= 10)
            grayscaleChannel = 10; //max grayscle channels is 10
        
        if (blur >= 2.2) {
            blur = 2.2;
        }
    }
    else if (key == OF_KEY_DOWN ) {
        grayscaleChannel--;
        blur--;
        
        cout << "grayscaleChannel: " << grayscaleChannel << endl;
        cout << "blur " << blur << endl;
        
        //cannot have less than 1 grayscale channel
        if (grayscaleChannel < 1) {
            grayscaleChannel = 1;
        }
        //cannot have less than 1 blur and edge channel
        if (blur <= 0.2) {
            blur = 0.2;
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
