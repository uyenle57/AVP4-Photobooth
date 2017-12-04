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
    ofVideoGrabber myCamera1;
    ofVideoGrabber myCamera2;
    ofVideoGrabber myCamera3;
    ofVideoGrabber myCamera4;
    
    ofPixels myPixels;
    ofPixels pix;
    
    
    // 4 textures for 4 effects
    ofTexture myTexture1;
//    ofTexture myTexture2;
//    ofTexture myTexture3;
//    ofTexture myTexture4;
    
    imageProc imageProc;
};
