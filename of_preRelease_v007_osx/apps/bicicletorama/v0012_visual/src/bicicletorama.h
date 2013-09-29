#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"
#include "game.h"
#include "kinect.h"
#include "borda.h"
#include "menu.h"
#include "apoio.h"



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
    
    ofArduino arduino;
	void setupArduino(const int & version);
    
    ofxBox2d box2d;
    
    game    m_game;
    kinect  m_kinect;
    menu	m_menu;
    apoio   m_apoio;
    
    
    
    borda m_borda;
};

