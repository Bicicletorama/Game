#pragma once

//fix C++ Redefinition Header Files
//http://stackoverflow.com/questions/1372480/c-redefinition-header-files
#include <winsock2.h>
#include <windows.h>

//must come first
#include "KinectInterface.h"

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"
#include "ofxTweenzor.h"
#include "Configuration.h"
#include "Arduino.h"
#include "game.h"
#include "Borda.h"
#include "Menu.h"
#include "panelUI.h"


class Bicicletorama : public ofBaseApp {
	
private:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
    
    
    
    ofxBox2d			box2d;
    
    Arduino				arduino;
    KinectInterface		kinect;
    Game				game;
    Menu				menu;
    Borda				borda;
    panelUI				m_panel;
    
};

