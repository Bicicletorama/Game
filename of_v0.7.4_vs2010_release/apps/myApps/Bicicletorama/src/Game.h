#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Config.h"
#include "Arduino.h"
#include "player.h"
#include "human.h"
#include "cop.h"
#include "bomb.h"
#include "civil.h"
#include "sound.h"


class Game {
    
public:
    
    void setup(b2World * _world, Arduino * _arduino);
    void update();
    void draw();
    
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
    
    void updatePlayersDirection(float direction[TOTAL_PLAYERS]);
    void updatePlayersDistance(float distance[TOTAL_PLAYERS]);
    
    player playerList[TOTAL_PLAYERS];
    
    
private:
    
    Arduino * arduino;
    b2World * world;
    
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
	
    vector <human*>	humans;

	void onCopAttack(attack & a);
		
	vector<bomb> bombs;
	ofFbo bombCanvas;
    
};