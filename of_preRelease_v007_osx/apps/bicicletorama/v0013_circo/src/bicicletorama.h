#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"
#include "config.h"
#include "game.h"
#include "kinect.h"
#include "borda.h"
#include "menu.h"
#include "arduino.h"
#include "panelUI.h"

class bicicletorama : public ofBaseApp {
	
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
    
    int width;
    int height;
    
    ofxBox2d box2d;
    
    arduino m_arduino;
    game    m_game;
    kinect  m_kinect;
    menu    m_menu;
    borda   m_borda;
    panelUI m_panel;
};

