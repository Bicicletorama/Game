/*
 *  dot.h
 *  mappingengine
 *
 *  Created by Tommy Lindestroem on 01/26/11.
 *  Copyright 2010 Superuber. All rights reserved.
 *
 */

#pragma once
#include <iostream>
#include "renderManager.h"

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"
#include "ofxThread.h"
#include "ofxXmlSettings.h"
#include "ofx3DModelLoader.h"
#include "ofEvents.h"

using namespace std;

class dot
{
	public :
	dot(void);
	~dot(void);
	void allocate(void);
	void update(void);
	void draw(void);
	void setRadius(int rad);
	void keyReleased(int key);
	
	double x;
	double y;
	int r;
	int g;
	int b;
	int rUnSel;
	int gUnSel;
	int bUnSel;
	int rad;
	
};



