#pragma once

#include "Box2d.h"
#include "ofxBox2d.h"
#include "ofxSpriteManager.h"


class player {
        
public:
    
    void setup(int _playerID, b2World * b2dworld);
    void update(int potenciometro, int reed, bool useArduino);
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
    float   steeringAngle;
    
    bool    idle;
    int     lastImpulseTime;
    
    ofxSprite           spriteBike;
    ofxSprite           spriteFront;
    
};

