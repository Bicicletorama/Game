#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "player.h"


#define TOTAL_PLAYERS 4


class bicicletorama : public ofBaseApp {
	
public:
	
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
    
	int	kk;//debug para ultima tecla apertada
    
	
	ofxBox2d							box2d;			//	the box2d world
	vector			<ofxBox2dCircle>	obstaculos;		//	obst‡culos adicionados na mesa
	
    player playerList[TOTAL_PLAYERS];
	
};

