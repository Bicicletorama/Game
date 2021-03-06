#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxTweenzor.h"
#include "Config.h"
#include "Arduino.h"
#include "player.h"
#include "human.h"
#include "cop.h"
#include "bomb.h"
#include "civil.h"
#include "sound.h"
#include "game/NPCControl.h"
#include "game/GenericData.h"
#include "game/PowerChange.h"


class Game {
    
public:
    
    void setup(ofxBox2d * _box2d, Arduino * _arduino);
    void update();
    void draw();
    
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
    
    player playerList[TOTAL_PLAYERS];

	NPCControl aiControl;
	bool knocksCop;

	//STATES
	enum states {RACE, RIOT};
	states state;
	void toggleState();
	void changeState(states state);
    

private:
    
	ofxBox2d * box2d;
    b2World * world;
    Arduino * arduino;
    
    void    startGame();
    int     startGameMillis;
    int     startGameTimer;
    int     lastGameTimer;
    
    bool locked;
	float delayedCall;
    
    ofImage background;
    ofFbo canvas;   
    
    ofxSprite largada;
    ofxSprite cabecas;
    int currentCabeca;
    
    vector <ofxBox2dCircle>	obstaculos;
	
	void onRiotWin(int & n);
	void onRiotLose(int & n);
	void showEndScreen(ofImage * image);
	void onShowEndScreenComplete(float* arg);
	void hideEndScreen(float* arg);

	ofImage winScreen;
	ofImage loseScreen;
	ofImage * endScreen;
	float endScreenAlpha;
	
    PowerChange powerUp;
    PowerChange powerDown;


	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
	
	void checkContactStart_powerChange(b2Fixture * a, b2Fixture * b);
	void checkContactEnd_powerChange(b2Fixture * a, b2Fixture * b);
	
	void checkContactStart_cop(b2Fixture * a, b2Fixture * b);

};