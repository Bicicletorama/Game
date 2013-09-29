/*
 *  distorter.cpp
 *  distortion
 *
 *  Created by Tommy Lindestroem on 05/11/12.
 *  Copyright 2012 Superuber. All rights reserved.
 *
 */

#include "distorter.h"


void distorter::init( int width, int height )
{
	XML.loadFile( "distortion.xml");
	
	this->height = height;
	this->width = width;
	
	doCalibrate = false;
	doMask		= false;
	
	cornerActive = 0;
	
	point = new ofPoint[4];
	
	XML.pushTag("main", 0);
		point[0].x = XML.getValue("point:x", 0, 0);
		point[0].y = XML.getValue("point:y", 0, 0);
	
		point[1].x = XML.getValue("point:x", 0, 1);
		point[1].y = XML.getValue("point:y", 0, 1);
		
		point[2].x= XML.getValue("point:x", 0, 2);
		point[2].y = XML.getValue("point:y", 0, 2);
	
		point[3].x= XML.getValue("point:x", 0, 3);
		point[3].y = XML.getValue("point:y", 0, 3);
	XML.popTag();	
	
	oDot.r = 0;
	oDot.g = 174;
	oDot.b = 239;
	
	this->rm.allocateForNScreens(1, width, height);
	
	reposition();
	
	x1 = y1 = x2 = y2 = x3 = y3 = x4 = y4 = 10;
	
	ofAddListener(ofEvents.keyPressed, this, &distorter::_keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &distorter::_keyReleased);
	ofAddListener(ofEvents.mousePressed, this, &distorter::_mousePressed);
	ofAddListener(ofEvents.mouseMoved, this, &distorter::_mouseMoved);
	
	Mask::setup(0,0);
}

void distorter::update(ofEventArgs & args)
{
	//if (this->bSaveMask)
	//	Mask::saveMask();
}


void distorter::renderBegin(void)
{
	
	
	this->rm.startOffscreenDraw();
	
	
}

void distorter::renderEnd(void)
{
	
	this->rm.endOffscreenDraw();	
	ofEnableAlphaBlending();
		this->rm.drawScreen(0);
	ofDisableAlphaBlending();
	
	Mask::draw(mouseX, mouseY);
	
	if ( doCalibrate )
	{
		oDot.x = point[ cornerActive ].x;
		oDot.y = point[ cornerActive ].y;		
		oDot.draw();
	}
	
	if ( doMask ) Mask::bActivePaint = true;			
	else Mask::bActivePaint = false;

	ofSetColor( 255,255,255 );
}


void distorter::reposition(void)
{
	for ( int i = 0; i < 4; i++ )
	{
		this->rm.outputPositions[0][i].x = point[i].x;
		this->rm.outputPositions[0][i].y = point[i].y;		
	}	
}


void distorter::_keyPressed  ( ofKeyEventArgs &e )
{
	
	if ( e.key == OF_KEY_LEFT  ) point[cornerActive].x -= 1; 
	if ( e.key == OF_KEY_RIGHT ) point[cornerActive].x += 1;
	if ( e.key == OF_KEY_UP    ) point[cornerActive].y -= 1; 
	if ( e.key == OF_KEY_DOWN  ) point[cornerActive].y += 1;
	if ( e.key == OF_KEY_BACKSPACE ) Mask::bIsShiftDown = true;
	
	if ( e.key == 't' ) Mask::height++;
	if ( e.key == 'y' ) Mask::height--;
	if ( e.key == 'u' ) Mask::width++;
	if ( e.key == 'i' ) Mask::width--;
	
	if ( e.key == 'm' ) {
		if ( doMask ) doMask = false;
		else doMask = true; 
	}
	
	if ( e.key == 'c' ) {
		if ( doCalibrate ) doCalibrate = false;
		else doCalibrate = true; 
	}
	

	if ( e.key == '1' ) cornerActive = 0;
	if ( e.key == '2' ) cornerActive = 1;
	if ( e.key == '3' ) cornerActive = 2;
	if ( e.key == '4' ) cornerActive = 3;
	
	if ( e.key == 's' ) save();
	
	if (e.key == OF_KEY_BACKSPACE) Mask::bIsShiftDown = true;
	
	
	
	reposition();
}

void distorter::_keyReleased  ( ofKeyEventArgs &e )
{
	Mask::bIsShiftDown = false;
}



void distorter::_mousePressed(ofMouseEventArgs &e) 
{
	if ( doMask ) Mask::paint( e.x, e.y, e.button);
	
	
}

void distorter::_mouseMoved(ofMouseEventArgs &e) 
{
	mouseX = e.x;
	mouseY = e.y;
}

void distorter::save()
{
	XML.clear();
	
	XML.addTag("main");
	for ( int i = 0; i < 4; i++ )
	{
		XML.pushTag("main", 0);
			int xposMain = XML.setValue( "point:x", ofToString( point[i].x ), i);
			int yposMain = XML.setValue( "point:y", ofToString( point[i].y ), i);
		XML.popTag();
	}
	
	
	
	
	XML.saveFile("distortion.xml");
	
	Mask::saveMask();
}

distorter::~distorter(void)
{
	
}