#pragma once

#include "ofMain.h"
#include "Configuration.h"
#include "VelStats.h"
#include "ofTrueTypeFont.h"


class Menu
{
    
public:
    
	float x1;
	float y1;
	float width1;
	float height1;
    ofTrueTypeFont myFont;
    
	void setup();
    void update(player playerList[TOTAL_PLAYERS]);
    void draw();
	
    void startTimer();
	void stopTimer();
    
    void keyReleased(int key);
    
    string toTimeCode(double milliseconds);
	
    
private:
    
    VelStats   m_stats;
	
	bool timerRunning;
	float timerCount;
	string displayTimer;
	
	ofImage image;
	
	double round(double val);
};