#pragma once

#include "Box2d.h"
#include "ofxBox2d.h"
#include "ofxSpriteManager.h"



#define BIKE_HEIGHT 30
#define BIKE_WIDTH 5
#define WHEEL_HEIGHT 10
#define WHEEL_WIDTH 2.5

#define BIKE_DENSITY 1
#define BIKE_BOUNCE 0.5
#define BIKE_FRICTION 0.1

#define HORSEPOWERS 20
#define STEER_SPEED 1.5
#define MAX_STEER_ANGLE PI/2.5
#define FLOOR_FRICTION 0.9

#define MAX_IDLE_TIME 300




class player {
	
public:
	player();
    
	void setup(int _playerID, b2World * b2dworld);
    
    void goToStartPosition();
    
    void setDirectionIncrement(float increment);
    void setDirection(float value);
    void applyImpulse(float value);
    
    void update();
    void draw();
     
    
private:
    void killOrthogonalVelocity(b2Body* targetBody);
    
	void wakeUp();
	void sleep();
    
    int playerID;
    
    ofxBox2dRect bike;
    ofxBox2dRect frontWheel;
    ofxBox2dRect rearWheel;
    b2RevoluteJoint* frontJoint;
    
    float engineSpeed;
    float steeringAngle;
    
    bool firstImpulse;
    
    bool idle;
    int idleTime;
    
    ofImage imageFrontWheel;
    ofImage imageBike;
    
    ofxSprite sprite;

    
};

