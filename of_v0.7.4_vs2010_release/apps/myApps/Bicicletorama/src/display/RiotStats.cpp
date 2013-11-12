
#include "RiotStats.h"


void RiotStats::setup()
{   
    minMilesecondsInterval = 2000;
    
    color[0] = 0xf9222b;
    color[1] = 0x22F960;
    
    for(int i=0; i<2; i++) data[i] = 0;
	
	avatar[0].loadImage("images/human/cabecas/3.png");
	avatar[1].loadImage("images/human/cabecas/2.png");
}

void RiotStats::update(NPCControl aiControl)
{
    if (ofGetElapsedTimeMillis()-lastTime<minMilesecondsInterval) return;
    lastTime = ofGetElapsedTimeMillis();
	
	Tweenzor::add(&data[0], data[0], aiControl.copsStatus.count / aiControl.copsStatus.max, 0.f, 2.f, EASE_OUT_ELASTIC);
	Tweenzor::add(&data[1], data[1], aiControl.civilsStatus.count / aiControl.civilsStatus.max, 0.f, 2.f, EASE_OUT_ELASTIC);
}

void RiotStats::draw()
{
    ofSetColor(0,100);
    ofRect(x, y, width, height);
    
	float yy, ww;
    for(int i=0; i<2; i++)
    {
		yy = y+13*i+15;
		ww = width*data[i];

        ofSetHexColor(color[i]);
		ofRect(x, yy, ww, 10);

		ofSetColor(255);
		avatar[i].draw(x+ww-5, yy-3);
    }
}
