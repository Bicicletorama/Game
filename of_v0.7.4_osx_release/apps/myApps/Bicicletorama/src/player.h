#pragma once

#include "Box2d.h"
#include "ofxBox2d.h"
#include "ofxSpriteManager.h"
#include "config.h"


class player {
        
public:
    float BIKE_HEIGHT;
    float BIKE_WIDTH;
    float WHEEL_HEIGHT;
    float WHEEL_WIDTH;
    
    float BIKE_DENSITY;
    float BIKE_BOUNCE;
    float BIKE_FRICTION;
    
    float HORSEPOWERS;
    float MAX_DIRECTION_ANGLE;
    float FLOOR_FRICTION;
    
    float MAX_IDLE_TIME;
    
    void setup(int _playerID, b2World * b2dworld);
    void update();
    void draw();
    
    void goToStartPosition();
    
    void setDirectionIncrement(float increment);
    void setDirection(float value);
    void applyImpulse();
    
    float getVelocity();

    int x;
    int y;

    int oldX;
    int oldY;

    ofColor color;
    
     
private:
    
    void killOrthogonalVelocity(b2Body* targetBody);
    
    void wakeUp();
    void sleep();
    
    int playerID;

    int lastReed;
    
    ofxBox2dRect        bike;
    ofxBox2dRect        frontWheel;
    ofxBox2dRect        rearWheel;
    b2RevoluteJoint*    frontJoint;
    
    float   engineSpeed;
    float   directionAngle;
    
    bool    idle;
    int     lastImpulseTime;
    
    ofxSprite           spriteBike;
    ofxSprite           spriteFront;
    
};

