#pragma once

#include "ofMain.h"
#include "apoio.h"

class testApp : public ofBaseApp{

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
		void windowResized(int w, int h);

		// we don't actually use these
        // just checking to see if they
        // all work in the same place :)
	
	int oldX;
	int oldY;
	
	apoio m_apoio;
};
