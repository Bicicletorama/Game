#include "apoio.h"
	
void apoio::setup()
{
    currentName = 0;
    totalName = 2;
    
    lastTime = ofGetElapsedTimeMillis();
    
    nameList[0] = stringUtils::subsChars("João");
    nameList[1] = "Maria";
    nameList[2] = "Jos\xE3";
    
    font.loadFont("fonts/verdana.ttf", 12, false);
}

void apoio::update()
{
    if (ofGetElapsedTimeMillis() - lastTime > 1000) 
    {
        lastTime = ofGetElapsedTimeMillis();
        
        currentName++;
        if (currentName > totalName) {
            currentName = 0;
        }
    }
}

void apoio::draw()
{
    ofPushStyle();
    ofSetHexColor(0xffffff);
    font.drawString("APOIOS", 30, 420);
    font.drawString(nameList[currentName], 30, 450);
    ofDrawBitmapString(nameList[currentName], 30, 480);
    ofPopStyle();
}