#pragma once


#include "ofMain.h"
#include "game.h"


class menu {
	
public:
	float x;
	float y;
	float width;
	float height;
	
	void setup(){
		logo.loadImage("logo.jpg");
		
		width = 1280 - 40;
		height = 40;
		x = 20;
		y = 800 - height - 20;
	}
	
    void update(player playerList[TOTAL_PLAYERS]){
		m_stats.update(playerList);
		
		if(timerRunning){
			int timer = ofGetElapsedTimeMillis() - timerCount;
			displaytTimer = "";
		}
	}
	
    void draw(){
		
		ofPushMatrix();
		ofTranslate(x, y, 0);
		
		logo.draw(0,0);
		
		m_stats.draw();
		
		//Draw displaytTimer
		
		ofPopStyle();
	}
	
	void startTimer(){
		timerRunning = true;
		timerCount = ofGetElapsedTimeMillis();
	}
	
	void stopTimer(){
		timerRunning = false;
	}
   	

	
private:
    stats   m_stats;
	
	bool timerRunning;
	float timerCount;
	string displayTimer;
	
	ofImage logo;
	
};