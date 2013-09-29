/*
 *  distorter.h
 *  distortion
 *
 *  Created by Tommy Lindestroem on 05/11/12.
 *  Copyright 2012 Superuber. All rights reserved.
 *
 */

#pragma once
#include <iostream>
#include "renderManager.h"
#include "ofMain.h"
#include "dot.h"
#include "Mask.h"

using namespace std;

class distorter
{
	public :
	~distorter(void);
	void init(int width, int height);
	void update( ofEventArgs & args );
	void renderBegin(void);
	void renderEnd(void);
	void reposition(void);
	void _keyPressed  ( ofKeyEventArgs &e );
	void _keyReleased ( ofKeyEventArgs &e );
	void _mouseMoved(ofMouseEventArgs &e);
	void _mousePressed(ofMouseEventArgs &e);
	
	void save();
	
	int cornerActive, height, width, x1 ,y1, x2, y2, x3, y3, x4, y4;
	
	renderManager		rm;
	dot					oDot;
	ofPoint *			point;
	bool				doCalibrate;	
	bool				doMask;
	ofxXmlSettings		XML;
	
	int mouseX, mouseY;
	
};



