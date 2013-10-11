#pragma once

#include "ofMain.h"
#include "Configuration.h"


class Arduino : public ofSerial
{
    
public:
    
	void setup();
	void update();
    
    int getImpulse(int playerID);
    float getDirection(int playerID);
    
    
private:
    
    string buffer;
    
    int impulse[TOTAL_PLAYERS];
    float direction[TOTAL_PLAYERS];

		
};

