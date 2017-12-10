#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //5 cameras
    ofVideoGrabber grayScaleCamera;
    ofVideoGrabber motionBlurCamera;
    ofVideoGrabber frameDiffCamera;
    ofVideoGrabber highPassCamera;
    ofVideoGrabber invertedCamera;
    
    //5 sets of pixels for each camera
    ofPixels myPixels1, pix1;
    ofPixels myPixels2, pix2;
    ofPixels myPixels3, pix3, lastPixels, blockPix;
    ofPixels myPixels4, pix4;
    ofPixels myPixels5, pix5;
    
    // 5 textures for 5 filters
    ofTexture grayscaleTexture;
    ofTexture motionBlurTexture;
    ofTexture highPassTexture;
    ofTexture frameDiffTexture;
    ofTexture invertedTexture;
    
    int numChannel = 3; //each pixel requires 3 bytes for storing R,B,G values (assumes its using RGB)
    int grayscaleChannel = 1; //for greyscale
    
    float lastVals1[9];
    float lastVals2[9];
    float blur = 0.2;
    
    ofImage snapshot; //for taking and saving snapshots

};
