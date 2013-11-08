#pragma once


#include "Configuration.h"
#include "ofxBox2d.h"
#include "game/GenericData.h"


class PowerChange {

public:

	PowerChange();
	~PowerChange();
	
	void setup(b2World * world, float isPowerUp);
	void update();
	void draw();
	
	void showAt(float x, float y);
    bool enabled;

protected:

	float value;

	int millis;

	ofImage image;
    ofxBox2dBaseShape * body;

};