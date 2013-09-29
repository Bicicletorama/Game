
#ifndef bicicletorama_Scenario_h
#define bicicletorama_Scenario_h


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"
#include "distorter.h"
#include "ofxUI.h"
#include "ofxTSPSUtils.h"



class Scenario {
    
public:
    
    void setup(int _width, int _height, b2World* _world);
    void update();
    void draw();
    void keyPressed(int key);
	void exit();
    
private:
    
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


#endif
