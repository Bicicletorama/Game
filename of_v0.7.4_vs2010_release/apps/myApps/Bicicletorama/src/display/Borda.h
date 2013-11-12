#pragma once

#include "ofMain.h"
#include "Configuration.h"
#include "ofxOpenCv.h"


class Borda
{
    
public:
    
    void setup(ofxCvContourFinder * _contourFinder);
    void update();
    void draw();
    
    ofxCvContourFinder * contourFinder;
    
private:
    
	ofVideoPlayer bg;
    ofImage mask;
    
    int border;
    
};