#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "config.h"
#include "arduino.h"
#include "player.h"
#include "sound.h"


class game {
    
public:
    
    void setup(int _width, int _height, b2World* _world);
    void update(float guidao[TOTAL_PLAYERS], float velo[TOTAL_PLAYERS]);
    void draw();
    
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
    
    player playerList[TOTAL_PLAYERS];
    
private:
    
    int width;
    int height;
    b2World* world;
    
    void    startGame();
    int     startGameMillis;
    int     startGameTimer;
    int     lastGameTimer;
    
    bool locked;
    
    ofImage background;
    ofFbo canvas;   
    
    ofxSprite largada;
    ofxSprite cabecas;
    int currentCabeca;
    
    vector <ofxBox2dCircle>	obstaculos;
    
};