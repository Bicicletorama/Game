#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"


class Borda
{
    
public:
    
    void setup(ofxCvContourFinder * _contourFinder);
    void update();
    void draw();
    
    ofxCvContourFinder * contourFinder;
    
private:
    
    vector <ofImage> images;
    
    int changeInterval;
    int lastTime;
    
    int margin;
    
    ofPoint translate;
    
    int curImage;
    
    ofImage mask;
    
    int border;
    
};