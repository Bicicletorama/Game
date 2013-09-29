#pragma once

#include "ofMain.h"
#include "stringUtils.h"

class apoio {
	
public:
	
	void setup() {
		currentName = 0;
		totalName = 2;
		
		lastTime = ofGetElapsedTimeMillis();
		
		nameList[0] = stringUtils::subsChars("João");
		nameList[1] = "Maria";
		nameList[2] = "Jos\xE3";
		
		font.loadFont("fonts/verdana.ttf", 12, false);
	}
	
	void update() {
		if (ofGetElapsedTimeMillis() - lastTime > 1000) 
		{
			lastTime = ofGetElapsedTimeMillis();
			
			currentName++;
			if (currentName > totalName) {
				currentName = 0;
			}
		}
	}
	
	void draw() {
		ofPushStyle();
		ofSetHexColor(0xffffff);
		font.drawString("APOIOS", 100, 50);
		font.drawString(nameList[currentName], 100, 100);
		ofDrawBitmapString(nameList[currentName],	100,150);
		ofPopStyle();
	}
		
private:
	
	int currentName;
	int totalName;
	
	int lastTime;
	
	string nameList[3];
	
	ofTrueTypeFont font;
	
};
