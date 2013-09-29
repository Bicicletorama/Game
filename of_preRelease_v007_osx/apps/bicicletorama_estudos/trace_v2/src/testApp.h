#pragma once

#include "ofMain.h"
#include "ofxBlur.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		void drawNew();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	ofFbo fboNew;
	ofFbo fboComp;
	ofFbo fboBlur;
	
	ofFbo canvas;
    
	ofxBlur blur;
    
    ofImage bg;
	
	int oldX;
	int oldY;
};
