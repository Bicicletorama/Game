#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"
#include "distorter.h"
#include "ofxUI.h"
#include "ofxTSPSUtils.h"


class kinect {
    
public:
    
    void setup(int _width, int _height, b2World* _world);
    void update();
    void draw();
    void keyPressed(int key);
	void exit();
    
    
    ofxCvGrayscaleImage         scaledImage;
    
    
    int width;
    int height;
    b2World* world;    
    
    
    ofxKinect					kinect;
	ofxCvColorImage				colorImg;
	ofxCvGrayscaleImage			grayImage; 
	ofxCvGrayscaleImage			grayImage2; 
	ofxCvGrayscaleImage			grayThreshNear; 
	ofxCvGrayscaleImage			grayThreshFar; 
	ofxCvContourFinder			contourFinder;
    
	int							nearThreshold;
	int							farThreshold;
	int							angle;
	int							nbCircles;
	int							threshold;
	int							blur;
	
	
	int kinectWidth, kinectHeight;
	
	vector <ofxBox2dCircle>		circles;
	vector <ofxBox2dPolygon>	polys;
	
	ofxTriangle					triangle;
    distorter rm;
    
    
    bool useRegCam;
    ofVideoGrabber 		vidGrabber;
	
	int minBlobSize;
	int maxBlobSize;
	
	bool                    showRawKinect;
    bool                    debugKinect;
    bool                    showCropped;
    bool                    showContour;
	
	ofxCvGrayscaleImage		kinectOutput;
	ofxCvGrayscaleImage		kinectOutputCropped;
	ofxCvGrayscaleImage		kinectOutputCropped2;
	vector <ofPoint>		quadCropCorners;
	
	unsigned char* fullSize;
	unsigned char* fullSize2;
	
    ofxCvGrayscaleImage 	transImage;
	ofxCvGrayscaleImage 	finalImage;
	
	int sizer;
	
	//UI
	void setGUI1();     
	void setGUI2();     
	
	ofxUICanvas *gui1;  
	ofxUICanvas *gui2;  
	
	void guiEvent(ofxUIEventArgs &e);
    
	void save();

};
