#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Project 4: Photobooth
 
 by Uyen Le
 tle004@gold.ac.uk
 
 ----------------
 A simple photobooth that has 5 different live camera pixels processing.
     - camera 1: grayscale with threshold
     - camera 2: motion blur
     - camera 3: high pass
     - camera 4: frame differencing
     - camera 5: inverted colours
 
 ----------------
 Credits:
 - imageProc.cpp
 - http://openframeworks.cc/ofBook/chapters/image_processing_computer_vision.html#acompleteworkflowbackgroundsubtraction
 */

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    
    //Allocate memory for the cameras
    //which is also the dimensions of the camera
    grayScaleCamera.initGrabber(320,240); //width=320; height=240
    motionBlurCamera.initGrabber(320,240);
    frameDiffCamera.initGrabber(320,240);
    highPassCamera.initGrabber(320,240);
    invertedCamera.initGrabber(320,240);
    
    //Allocate pixels for the cameras
    //by getting the camera's width, height and number of channels
    //3 channels for Red, Green, Blue
    myPixels1.allocate(grayScaleCamera.getWidth(), grayScaleCamera.getHeight(), 1);
    myPixels2.allocate(motionBlurCamera.getWidth(), motionBlurCamera.getHeight(), numChannel);
    myPixels3.allocate(frameDiffCamera.getWidth(), frameDiffCamera.getHeight(), 1);
    lastPixels.allocate(frameDiffCamera.getWidth(), frameDiffCamera.getHeight(), numChannel);
    myPixels4.allocate(highPassCamera.getWidth(), highPassCamera.getHeight(), numChannel);
    myPixels5.allocate(invertedCamera.getWidth(), invertedCamera.getHeight(), numChannel);
    invertedTexture.allocate(invertedCamera.getWidth(), invertedCamera.getHeight(), numChannel);

}

//--------------------------------------------------------------
void ofApp::update(){

    /* Below are the implementations of the 5 cameras with 5 different filters.
        The implementations of all the cameras are the same, the only difference is in the for-loop which manipulates and processes the pixels differently for each filter.
     */
    
    // ============ CAMERA 1: THRESHOLD GREYSCALE ============
    
    // Get fresh data from the video
    grayScaleCamera.update();
    
    //If there is fresh data
    if (grayScaleCamera.isFrameNew()) {
        
        pix1 = grayScaleCamera.getPixels(); //store all the pixels of the camera into 'pix1'

        //Loop through every byte of the RGB camera
        //Hard threshold the image and make it greyscale.
        for (int i =0; i < grayScaleCamera.getWidth()*grayScaleCamera.getHeight(); i += grayscaleChannel) {
            
            int index = i*3; //multiply by 3 for the 3 channels R,G,B
            
            // 0.2126*R + 0.7152*G + 0.0722*B
            myPixels1[i]=(pix1[index] * 0.2126) + (pix1[index+1] * 0.7152) + (pix1[index+2] * 0.0722);
            // myPixels1[i] is the i'th byte of the image
            // which contains the values of the 3 channels: R,B,G
            
            // Set the threshold
            if (myPixels1[i] > 128) //if current pixel colour is more than threshold level of 128
                myPixels1[i] = 255; //set it to white
            else
                myPixels1[i] = 0; //otherwise set it to black
        }
        
        // Allocate the pixels transformations into corresponding texture of the camera
        grayscaleTexture.allocate(myPixels1);
    }


    // ============ CAMERA 2: MOTION BLUR ============
    motionBlurCamera.update();

    if(motionBlurCamera.isFrameNew()) {

        pix2 = motionBlurCamera.getPixels();
        
        //Loop through every byte of the RGB camera (which includes camera's width, height and number of channels
        for(int i=0; i < motionBlurCamera.getWidth()*motionBlurCamera.getHeight()*numChannel; i++) {
 
            // lastVals1[i%3] makes sure that RGB value never goes beyond array size of 9
            // add a small amount of blur (0.02)
            // then multiply with pix2[i] - lastVals1[i%3] which is the difference in colour of each pixel between the current frame and the previous frame
            // this creates new colour for each pixel
            myPixels2[i] = lastVals1[i%3] + blur * (pix2[i] - lastVals1[i%3]);

            // once used, store the RGB values of the pixel position of the current frame as the previous frame
            // so the next frame can continue using it
            lastVals1[i%3] = myPixels2[i];
        }
        
        motionBlurTexture.allocate(myPixels2);
    }


    // ============ CAMERA 3: HIGH PASS ============
    highPassCamera.update();
    
    if(highPassCamera.isFrameNew()) {
        
        pix4 = highPassCamera.getPixels();
        
        for(int i=0; i < highPassCamera.getWidth()*highPassCamera.getHeight()*numChannel; i++) {
            
            myPixels4[i] = lastVals2[i%3] + blur * (pix4[i] - lastVals2[i%3]); //same as Motion blur
            
            // once used, store the RGB values of the pixel position of the current frame as the previous frame
            // so the next frame can continue using it
            lastVals2[i%3] = myPixels4[i];
            
            myPixels4[i] = pix4[i]-myPixels4[i];
        }
        
        highPassTexture.allocate(myPixels4);
        
    }
    
    
    // ============ CAMERA 4: FRAME DIFFERENCING ============
    // A simple background subtraction method
    // Displays white lines when there is energy/movement (e.g. there is difference between current and previous frame)
    // More movement = more whiteness
    
    frameDiffCamera.update();

    if(frameDiffCamera.isFrameNew()) {
        
        pix3 = frameDiffCamera.getPixels();

        for (int i = 0; i < frameDiffCamera.getWidth(); i++){
            for (int j = 0; j < frameDiffCamera.getHeight(); j++) {
                
                //Frame Difference on the red channel
                //by subtracting the R channel values of the previous frame with that of the current frame
                //then compute the absolute value of this difference so that the number is always positive
                
                int width = frameDiffCamera.getWidth(); //320
    
                // lastPixels[(j*320+i)*3]) is the previous frame
                // pix3[(j*320+i)*3] is the current frame
                myPixels3[(j*width+i)] = abs((lastPixels[(j*width+i)*3]) - (pix3[(j*width+i)*3]));

                // once used, store the value of the current frame's Red channel as the previous frame
                // so the next frame can continue using it
                lastPixels[(j*width+i)*3] = pix3[(j*width+i)*3];

            }
        }
        
        frameDiffTexture.allocate(myPixels3);
    }
    
    // ============ CAMERA 5: INVERTED / NEGATIVE COLOURS ============
    // This filter subtracts all the pixel colours from 255 to get the inverse colour value of each pixel
    //from http://openframeworks.cc/ofBook/chapters/image_processing_computer_vision.html#acompleteworkflowbackgroundsubtraction
    
    invertedCamera.update();
    
    if(invertedCamera.isFrameNew()) {
        
        pix5 = invertedCamera.getPixels();
        
        for (int i = 0; i < invertedCamera.getWidth()*invertedCamera.getHeight()*numChannel; i++){
            
            // subtract each pixel's current colour from 255 to get the inverse
            // then set that value as the new colour for each pixel
            // this makes the photo 'negative'
            myPixels5[i] = 255 - pix5[i];
        }
        invertedTexture.allocate(myPixels5);
    }
    
    /////////
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // Display 5 cameras
    grayscaleTexture.draw(20, 20);
    motionBlurTexture.draw(360,20);
    invertedTexture.draw(700, 20);
    highPassTexture.draw(20, 280);
    frameDiffTexture.draw(360, 280);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // Press space bar to take a photo!
    // Photo is saved in /bin/data/
    if (key == 32) {
        snapshot.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        snapshot.save("screenshot.png");
        cout << "Picture taken!" << endl;
    }
    
    //Press keys UP and DOWN to change filter effects
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
