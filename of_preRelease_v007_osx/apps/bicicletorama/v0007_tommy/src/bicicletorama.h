#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"
#include "player.h"
#include "distorter.h"
#include "ofxUI.h"
#include "ofxTSPSUtils.h"


#define TOTAL_PLAYERS 4


class bicicletorama : public ofBaseApp {
	
private:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	
    void startGame();
    
    ofArduino   arduino;

    float getSerialValue(char key);
    
    ofImage background;
    
    ofxBox2d box2d;
    player playerList[TOTAL_PLAYERS];
    vector <ofxBox2dCircle>	obstaculos;
    
    
	void setupArduino(const int & version);
    
    
    //KINECT + TRIANGLE
    void updateKinect();
    
    ofxKinect					kinect;
	ofxCvColorImage				colorImg;
	ofxCvGrayscaleImage			grayImage; 
	ofxCvGrayscaleImage			grayImage2; 
	ofxCvGrayscaleImage			grayThreshNear; 
	ofxCvGrayscaleImage			grayThreshFar; 
	ofxCvContourFinder			contourFinder;
    ofxCvGrayscaleImage         scaledImage;
    
    bool                        debugKinect;
	
	bool						bDrawPointCloud;
	
	int							nearThreshold;
	int							farThreshold;
	int							angle;
	int							nbCircles;
	int							threshold;
	int							blur;
	
	
	vector <ofxBox2dCircle>		circles;
	vector <ofxBox2dPolygon>	polys;
	
	ofxTriangle					triangle;
    distorter rm;
    
    
    //MAP
    float mapAngle;
    float mapCenterX;
    float mapCenterY;
    float mapScaleX;
    float mapScaleY;
    float mapMoveX;
    float mapMoveY;
	
    //RASTROS
    ofFbo canvas;
    int oldX;
    int oldY;
    
    
    int width;
    int height;
	
	bool useRegCam;
	 ofVideoGrabber 		vidGrabber;
	
	//UI
	
	void setGUI1();     
	void setGUI2();     
	
	ofxUICanvas *gui1;  
	ofxUICanvas *gui2;  
	
	void guiEvent(ofxUIEventArgs &e);
	
	int minBlobSize;
	int maxBlobSize;
	
	bool showRawKinect;
	
	ofxCvGrayscaleImage		kinectOutput;
	ofxCvGrayscaleImage		kinectOutputCropped;
	ofxCvGrayscaleImage		kinectOutputCropped2;
	vector <ofPoint>		quadCropCorners;
	
	void save();

};
