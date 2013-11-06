#pragma once

#include "ofMain.h"
#include "ofxSpriteManager.h"

class bomb : public ofBaseApp{
public:
	void setup(float xIn, float yIn, float xOut, float yOut)
	{
		startX = xIn;
		startY = yIn;
		endX = xOut;
		endY = yOut;
		
		diffX = startX - endX;
		diffY = startY - endY;

		totalSteps = 60;
		stepsPerFrame = 3;
		curStep = 0;
		
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
	}

	void update()
	{
		if(curStep==totalSteps){
			sprite.update();
		}
	}

	void draw()
	{
		if(curStep<totalSteps){
			for(int i=0; i<stepsPerFrame && curStep<totalSteps; i++){
				sprite.draw(ofVec2f(
					startX - (diffX*curStep/totalSteps),
					startY - (diffY*curStep/totalSteps)
				));
				curStep++;
			}
		}else{
			sprite.draw(endX, endY);
		}
	}

	bool hasComplete()
	{
		return !sprite.getIsPlaying();
	}

private:
    ofxSprite           sprite;

	float startX;
	float startY;

	float endX;
	float endY;

	float diffX;
	float diffY;

	float curStep;
	float stepsPerFrame;
	float totalSteps;
};
