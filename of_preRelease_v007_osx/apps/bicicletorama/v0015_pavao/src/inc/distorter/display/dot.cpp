/*
 *  dot.cpp
 *  mappingengine
 *
 *  Created by Tommy Lindestroem on 01/26/11.
 *  Copyright 2011 Superuber. All rights reserved.
 *
 */

#include "dot.h"


dot::dot(void)
{
	rad = 10;
}

void dot::update(void)
{
	
}

void dot::draw(void)
{
	ofSetColor( r,g,b );
	ofFill();
	ofCircle(this->x, this->y, rad);
}

void dot::setRadius(int rad)
{
	this->rad = rad;	
}

dot::~dot(void)
{
	
}