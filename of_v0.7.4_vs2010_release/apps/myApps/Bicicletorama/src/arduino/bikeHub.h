#pragma once

#include "ofMain.h"
#include "Configuration.h"


struct bikeConnection {
	bool isConnected;
	bool wheel;
	int totalWheel;
	float handlebar;
};

class bikeHub
{
    
public:
    
	bikeHub();
	~bikeHub();

	void setup();
	void update();
	
    bool isBikeConnected(int id);
    int getBikeImpulse(int id);
    float getBikeDirection(int id);
    
	bool isConnected;
    
    
private:
    
    ofSerial serial;
    string buffer;
	
	void onReceive();
	void parseConnection(int id, bool connection, bool wheel, float handlebar);

	bikeConnection connections[TOTAL_PLAYERS];
		
};

