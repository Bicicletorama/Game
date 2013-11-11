#pragma once

#include "ofMain.h"
#include "Configuration.h"
#include "VelStats.h"
#include "RiotStats.h"
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
    void update(player playerList[TOTAL_PLAYERS], NPCControl aiControl);
    void draw();
	
    void startTimer();
	void stopTimer();
    
    void keyReleased(int key);
    
    string toTimeCode(double milliseconds);
	
    
private:
    
    VelStats   m_stats;
    RiotStats   m_riot;
	
	bool timerRunning;
	float timerCount;
	string displayTimer;
	
	ofImage image;
	
	double round(double val);
};