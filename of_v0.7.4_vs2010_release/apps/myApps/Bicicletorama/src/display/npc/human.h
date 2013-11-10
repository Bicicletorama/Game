#pragma once

#include "Box2d.h"
#include "ofxBox2d.h"
#include "ofxSpriteManager.h"
#include "Configuration.h"
#include "player.h"
#include "game/GenericData.h"

struct attack {
	float startX;
	float startY;
	float endX;
	float endY;
};

class human {
        
public:
	~human();
	
	ofEvent<attack> onAttack;

	int MIN_CHANGE_TIME;

    int x;
    int y;
	float width;
	float height;

	float rotation;
    
    void setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS]);
    void update();
    void draw();
	void leave();
    
	//PHYSICS
    ofxBox2dRect        physics;

	//STATES
	enum states {IDLE, WALKING, ATTACKING, DYING, LEAVING};
	int state;
	void changeState(states _state);
	bool hasComplete();

protected:
    
	//AI
	void think();
	void startAtRandomPosition();
    
	//STATES
    double lastTimeIChanged;
	bool completed;

	//SPRITES
	ofxSprite *			sprite;
    ofxSprite           spriteIdle;
    ofxSprite           spriteWalking;
    ofxSprite           spriteAttacking;
    ofxSprite           spriteDying;

	//GAME
    player (* playerList)[TOTAL_PLAYERS];
	int closestPlayer;
	int findClosestPlayer(int _x, int _y);
	int playerDistance(int playerIndex, int _x, int _y);

	// MOVE
	void updatePosition();
	void updateRotation();
	float getDegrees(float radians);
	float getRadians(float delta_x, float delta_y);
	
    int oldX;
    int oldY;

	int destX;
	int destY;

	float distX;
	float distY;  
};