#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "player.h"


#define TOTAL_PLAYERS 4


class game {
    
public:
    
    void setup(int _width, int _height, b2World* _world, ofArduino _arduino);
    void update();
    void draw();
    
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
    
    player playerList[TOTAL_PLAYERS];
    
private:
    
    int width;
    int height;
    b2World* world;
    ofArduino arduino;
    
    void    startGame();
    int     startGameMillis;
    int     startGameTimer;
    
    bool locked;
    
    ofImage background;
    ofFbo canvas;    
    
    vector <ofxBox2dCircle>	obstaculos;
    
};