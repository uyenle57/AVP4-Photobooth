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
    
    //4 cameras for 4 effects
    ofVideoGrabber myCamera1;
    ofVideoGrabber myCamera2;
    ofVideoGrabber myCamera3;
    ofVideoGrabber myCamera4;
    
    ofPixels pixels, pixels2;
    
    ofPixels pixelout, lastPixels;
    
    // 4 textures for 4 effects
    ofTexture backgroundSubtraction;
//    ofTexture myTexture;
//    ofTexture myTexture;
//    ofTexture myTexture;
};
