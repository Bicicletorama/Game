#include "Menu.h"

void Menu::setup()
{
    image.loadImage("images/menu.png");
    
    myFont.loadFont("fonts/verdana.ttf", 22);
    
    width1 = WIDTH - 40;
    height1 = 40;
    x1 = 20;
    y1 = HEIGHT - height1 - 20;
    
    m_stats.setup();
    m_stats.x2 = x1 + 782;
    m_stats.y2 = y1;
    m_stats.width2 = 200;
    m_stats.height2 = 40;
    
    timerRunning = false;
    displayTimer = "";
    timerCount = 0;
    
    startTimer();
}

void Menu::update(player playerList[TOTAL_PLAYERS])
{
    m_stats.update(playerList);
    
    if(timerRunning){
        int timer = ofGetElapsedTimeMillis() - timerCount;
        displayTimer = toTimeCode(timer);
    }
    
    //cout << x1 << " - " << y1 << " - " << width1 << " - " << height1 << endl;
}

void Menu::draw()
{
    ofPushStyle();
    
    ofSetColor(0, 255);
    ofRect(x1,y1,width1, height1);
    
    ofSetColor(255,255,255,255);
    image.draw(x1,y1);
   
    myFont.drawString(displayTimer, x1+590, y1+32);
   
    m_stats.draw();
    
    ofSetColor(255);
    ofPopStyle();
}

void Menu::startTimer()
{
    timerRunning = true;
    timerCount = ofGetElapsedTimeMillis();
}

void Menu::stopTimer()
{
    timerRunning = false;
}

void Menu::keyReleased(int key) 
{    
    if (key == 'p') startTimer();
}

string Menu::toTimeCode(int milliseconds) {
    int seconds = round((milliseconds/1000) % 60);
    string strSeconds = (seconds < 10) ? ("0" + ofToString(seconds)) : ofToString(seconds);
    int minutes = round(floor((milliseconds/1000)/60));
    string strMinutes = (minutes < 10) ? ("0" + ofToString(minutes)) : ofToString(minutes);
    if(seconds == 60) strMinutes = "00";
    
    
    if(minutes > 60) {
        strSeconds = "60";
        strMinutes = "00";
    }
    
    return strMinutes + ":" + strSeconds;
}
