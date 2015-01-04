#pragma once

#include "ofMain.h"
#include "config.h"
#include "player.h"


static const int TOTAL_VEL = 100;


class VelStats {
        
public:
	
    float x2, y2;
	float width2;
	float height2;
	int minMilesecondsInterval;
	
	float color[4];
	
	void setup();
	void update(player playerList[TOTAL_PLAYERS]);
	void draw();
	
private:
    
	float _v1[TOTAL_VEL];
	float _v2[TOTAL_VEL];
	float _v3[TOTAL_VEL];
	float _v4[TOTAL_VEL];
	
	float max;
	
	int lastTime;    
    
};