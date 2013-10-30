#pragma once

//must come first
#include "ofxKinectNui.h"

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"
#include "Configuration.h"

#include "opencv2/core/core_c.h"

class KinectInterface {
    
public:
    
    void setup(b2World* _world);
    void update();
    void draw();
    void keyPressed(int key);
	void exit();
    
    void updateROI(int x, int y, int w, int h);
	void setAngle(int _angle);
    
    void captureBackground(bool clearBackground);
    
    ofxCvGrayscaleImage		scaledImage;
	ofxCvContourFinder		contourFinder;
    
	vector <ofPoint>		quadCropCorners;
	
	bool                    showKinect;
    bool                    showCropped;
    bool                    showContour;
    
    
	int	BLUR_AMOUNT;
	int MIN_BLOB_AREA;
    int TOLERANCE; //millimeter of invisible outline from any object found by kinect
    int SENSIBILITY; //number of frames readed with success to detect a real object by kinect
		
	ofxKinectNui kinect;
	bool bPlugged;

    
private:
    
	ofxCvGrayscaleImage depthImage;
	ofxCvGrayscaleImage thresholdedImage;
    
    ofPixels backgroundPixels;
    ofPixels lifePixels;
    
    
    int kinectNumPixels;
    int captureCount;
    
	int angle;
    
    b2World *                   world;
	vector <ofxBox2dPolygon>	polys;
    ofxTriangle					triangle;
    

};
