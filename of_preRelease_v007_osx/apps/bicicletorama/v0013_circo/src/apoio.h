#pragma once

#include "ofMain.h"
#include "utils/stringUtils.h"

class apoio {
	
public:
	
	void setup();	
	void update();	
	void draw();
    
private:
	
	int currentName;
	int totalName;
	
	int lastTime;
	
	string nameList[3];
	
	ofTrueTypeFont font;
	
};
