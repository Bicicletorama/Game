#pragma once

#include "ofMain.h"
#include "ofxSpriteManager.h"
#include "ofxTweenzor.h"

class bomb{
public:
	
	ofEvent<ofVec2f> onExplode;

	void setup(float xIn, float yIn, float xOut, float yOut)
	{	
		x = xIn;
		y = yIn;
		time = 0.0f;
		rotation = ofRandom(360);
		
		Tweenzor::add(&x, x, xOut, 0.f, 2.f, EASE_OUT_QUAD);
		Tweenzor::add(&y, y, yOut, 0.f, 2.f, EASE_OUT_QUAD);
		Tweenzor::add(&rotation, rotation, rotation+ofRandom(360), 0.f, 2.f);
		Tweenzor::add(&time, time, 1.f, 0.f, 2.f, EASE_OUT_BOUNCE);
        Tweenzor::addCompleteListener( Tweenzor::getTween(&time), this, &bomb::onTweenComplete);
		
		sprite.addFile("images/human/cop/explosion/0.png");
		sprite.addFile("images/human/cop/explosion/1.png");
		sprite.addFile("images/human/cop/explosion/2.png");
		sprite.addFile("images/human/cop/explosion/3.png");
		sprite.addFile("images/human/cop/explosion/4.png");
		sprite.addFile("images/human/cop/explosion/5.png");
		sprite.addFile("images/human/cop/explosion/6.png");
		sprite.addFile("images/human/cop/explosion/7.png");
		sprite.addFile("images/human/cop/explosion/8.png");
		sprite.addFile("images/human/cop/explosion/9.png");

		sprite.play();
		sprite.setLoop(false);
		sprite.setFrameRate(6);
		sprite.setAnchorPercent(0.5, 0.5);
	
		exploded = false;
	}

	void update()
	{
		scale = sin(PI*time)+1;
		if(exploded){
			sprite.update();
		}
	}

	void draw()
	{
		ofPushMatrix();
			ofTranslate(x, y);
			ofRotate(rotation);
			ofScale(scale, scale);
			sprite.draw();
		ofPopMatrix();
	}

	bool hasComplete()
	{
		return exploded && !sprite.getIsPlaying();
	}

private:
    ofxSprite           sprite;

	float x, y, scale, rotation, time;
	bool exploded;

	void onTweenComplete(float* arg) {
		exploded = true;
		ofVec2f pos = ofVec2f(x, y);
		ofNotifyEvent(onExplode, pos);
	}
};
