#pragma once

#include "ofMain.h"
#include "Config.h"


class Arduino : public ofSerial
{
    
public:
    
	void setup();
	void update();
    
    int getImpulse(int playerID);
    float getDirection(int playerID);
    float getClk(int playerID);
    
    
private:
    
    string buffer;
    
    int impulse[TOTAL_PLAYERS];
    float direction[TOTAL_PLAYERS];
    int clk[TOTAL_PLAYERS];
		
};

