#pragma once

#include "ofxBox2d.h"
#include "game/GenericData.h"


class PowerUp {
        
public:

	PowerUp(b2World * b2dworld);

	void update();
	void draw();

protected:
    
	ofImage image;
    ofxBox2dRect box;

};