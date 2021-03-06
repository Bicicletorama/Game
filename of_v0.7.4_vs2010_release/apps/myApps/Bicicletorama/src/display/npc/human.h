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
    
	//PHYSICS
    ofxBox2dRect        physics;

	//TYPES
	enum types {COP, CIVIL};
	int type;

	//STATES
	enum states {IDLE, WALKING, ATTACKING, DYING, RISING, LEAVING};
	bool hasComplete();
	int getState();
	void die();
	void leave();

protected:
    
	//AI
	void think();
	virtual void doSomething();
	void startAtRandomPosition();
    
	//STATES
    double lastTimeIChanged;
	bool completed;
	int state;
	void changeState(states _state);

	//SPRITES
	ofxSprite *			sprite;
    ofxSprite           spriteIdle;
    ofxSprite           spriteWalking;
    ofxSprite           spriteAttacking;
    ofxSprite           spriteDying;
    ofxSprite           spriteRising;
    ofxSprite           spriteLeaving;

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

	int destX;
	int destY;

	float distX;
	float distY; 
};