#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"

class kinectBox2d : public ofBaseApp 
{
	public:
	
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed (int key);
	
	ofxKinect					kinect;
	ofxCvColorImage				colorImg;
	ofxCvGrayscaleImage			grayImage; 
	ofxCvGrayscaleImage			grayThreshNear; 
	ofxCvGrayscaleImage			grayThreshFar; 
	ofxCvContourFinder			contourFinder;
	
	bool						bDrawPointCloud;
	
	int							nearThreshold;
	int							farThreshold;
	int							angle;
	int							nbCircles;
	
    ofxBox2d					physics;
	
	vector <ofxBox2dCircle>		circles;
	vector <ofxBox2dPolygon>	polys;
	
	ofxTriangle					triangle;
};
