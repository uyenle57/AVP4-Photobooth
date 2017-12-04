#pragma once

#include "ofMain.h"
#include "imageProc.hpp"

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
    
    //4 cameras for 4 effects
    ofVideoGrabber grayScaleCamera;
    ofVideoGrabber motionBlurCamera;
    ofVideoGrabber edgeDetectCamera;
    ofVideoGrabber highPassCamera;
    
//    ofPixels grayscalePixelsIn, grayscalePixelsOut;
//    ofPixels motionBlurPixelsIn, motionBlurPixelsOut;
    
    ofPixels myPixels1, pix1;
    ofPixels myPixels2, pix2;
    ofPixels myPixels3, pix3;
    ofPixels myPixels4, pix4;
    
    // 4 textures for 4 effects
    ofTexture grayscaleTexture;
    ofTexture motionBlurTexture;
    ofTexture edgeDetectTexture;
    ofTexture highPassTexture;
    
    imageProc imageProc;
    
    int numChannels = 1; //for greyscale
    float lastVals1[9];
    float lastVals2[9];
    float lastVals3[9];
    float blur = 2.0;
    float edge = 2.0;
};
