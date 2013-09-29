#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"
#include "Config.h"

#include "opencv2/core/core_c.h"


class Kinect {
    
public:
    
    void setup(b2World* _world);
    void update();
    void draw();
    void keyPressed(int key);
	void exit();
    
    void updateROI(int x, int y, int w, int h);
    
    void captureBackground(bool clearBackground);
    
    ofxCvGrayscaleImage         scaledImage;
	ofxCvContourFinder contourFinder;
    
	vector <ofPoint>		quadCropCorners;
	
	bool                    showKinect;
    bool                    showCropped;
    bool                    showContour;
    
    
	int	BLUR_AMOUNT;
	int MIN_BLOB_AREA;
    float TOLERANCE; //millimeter of invisible outline from any object found by kinect
    float SENSIBILITY; //number of frames readed with success to detect a real object by kinect
    int NEAR;
    int FAR;
    

    
private:
        
    ofxKinect kinect;
    
	ofxCvGrayscaleImage kinectImage;
    
    ofShortPixels backgroundPixels;
    ofPixels lifePixels;
    
    
    int kinectNumPixels;
    int captureCount;
    
	
    
    b2World *                   world;
	vector <ofxBox2dPolygon>	polys;
    ofxTriangle					triangle;
    

};
