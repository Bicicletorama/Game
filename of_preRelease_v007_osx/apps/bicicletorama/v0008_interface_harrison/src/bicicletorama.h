#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"
#include "player.h"
#include "distorter.h"



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
    int timerStartGame;
    
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

};

