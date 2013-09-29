#pragma once

#include "Box2d.h"
#include "ofxBox2d.h"
#include "ofxBox2dBaseShape.h"
#include "ofxBox2dRect.h"



#define BIKE_HEIGHT 30
#define BIKE_WIDTH 3
#define WHEEL_HEIGHT 15
#define WHEEL_WIDTH 5

#define DENSITY 1
#define BOUNCE 0.5
#define FRICTION 0.1

#define HORSEPOWERS 40
#define STEER_SPEED 1.5
#define MAX_STEER_ANGLE PI/2.5
#define FLOOR_FRICTION 0.9

#define MAX_IDLE_TIME 300



class player {
	
public:
	player();
    
	void setup(b2World * b2dworld, int _playerID);
    
    void start();
    
    void setDirectionIncrement(float increment);
    void setDirection(float value);
    void applyImpulse();
    
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
    
    bool idle;
    int idleTime;

    
};

