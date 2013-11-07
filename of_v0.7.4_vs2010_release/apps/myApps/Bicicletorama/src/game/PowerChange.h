#pragma once


#include "Configuration.h"
#include "ofxBox2d.h"
#include "game/GenericData.h"


class PowerChange {

public:
	
	void setup(b2World * b2dworld, float isPowerUp);
	void update();
	void draw();
	
	void showAt(float x, float y);
    bool enabled;

protected:

	float value;

	int millis;

	ofImage image;
    ofxBox2dRect box;

};