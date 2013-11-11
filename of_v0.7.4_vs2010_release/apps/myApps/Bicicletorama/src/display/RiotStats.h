#pragma once

#include "ofMain.h"
#include "Configuration.h"
#include "game/NPCControl.h"
#include "ofxTweenzor.h"


class RiotStats {
        
public:
	
    float x, y;
	float width;
	float height;
	int minMilesecondsInterval;
	
	float color[2];
	
	void setup();
	void update(NPCControl aiControl);
	void draw();
	
private:
    
	float data[2];
	
	int lastTime;    
    
};