#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "player.h"


#define TOTAL_PLAYERS 4

#define SERIAL_STRING_LENGTH 10


class bicicletorama : public ofBaseApp {
	
private:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	
    void startGame();
    
    ofArduino   arduino;

    float getSerialValue(char key);
    
    ofImage background;
    
    ofxBox2d box2d;
    player playerList[TOTAL_PLAYERS];
    vector <ofxBox2dCircle>	obstaculos;
    
    
	void setupArduino(const int & version);
	
};

