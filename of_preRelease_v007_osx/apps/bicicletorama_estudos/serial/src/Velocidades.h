/*
 *  Borda.h
 *  allAddonsExample
 *
 *  Created by Vamoss on 6/16/12.
 *  Copyright 2012 Vamoss. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

#define TOTAL_VEL	100

class Velocidades{
	
public:
	
	int width;
	int height;
	int minMilesecondsInterval;
	
	float color[4];
	
	void setup(){
		width = 600;
		height = 500;
		
		max = 50;
		
		minMilesecondsInterval = 100;
		
		color[0] = 0x22F960;
		color[1] = 0xFFF220;
		color[2] = 0xF9222B;
		color[3] = 0x22D3F9;
		
		for(int i=0; i<TOTAL_VEL; i++){
			_v1[i] = 1;
			_v2[i] = 1;
			_v3[i] = 1;
			_v4[i] = 1;
		}
	}
	
	void update(){
		
	}
	
	void addValues(float v1, float v2, float v3, float v4) {
		if(ofGetElapsedTimeMillis()-lastTime<minMilesecondsInterval) return;
		lastTime = ofGetElapsedTimeMillis();
		
		max = 1;
		
		for(int i=TOTAL_VEL-1; i>=0; i--){
			cout << _v1[i] << ", ";
			if(i==0){
				_v1[i] = v1;
				_v2[i] = v2;
				_v3[i] = v3;
				_v4[i] = v4;
			}else{
				_v1[i] = _v1[i-1];
				_v2[i] = _v2[i-1];
				_v3[i] = _v3[i-1];
				_v4[i] = _v4[i-1];
			}
			
			if(_v1[i]>max) max = _v1[i];
			if(_v2[i]>max) max = _v2[i];
			if(_v3[i]>max) max = _v3[i];
			if(_v4[i]>max) max = _v4[i];
		}
		
		cout << endl;
	}
	
	void draw(float x, float y){
		ofPushStyle();
		ofTranslate(x, y, 0.0);
		ofSetHexColor(0x111111);
		ofRect(0,0,width, height);
		
		float pag = width / TOTAL_VEL;
		float pagAtual;
		float pagProx;
		
		
		for(int i=0; i<TOTAL_VEL-1; i++){
			pagAtual = pag*i;
			pagProx = pag*(i+1);
		
			
			ofSetHexColor(color[0]);
			ofLine(pagAtual, height-(_v1[i]/max*height), pagProx, height-(_v1[i+1]/max*height));
			
			ofSetHexColor(color[1]);
			ofLine(pagAtual, height-(_v2[i]/max*height), pagProx, height-(_v2[i+1]/max*height));
			
			ofSetHexColor(color[2]);
			ofLine(pagAtual, height-(_v3[i]/max*height), pagProx, height-(_v3[i+1]/max*height));
			
			ofSetHexColor(color[3]);
			ofLine(pagAtual, height-(_v4[i]/max*height), pagProx, height-(_v4[i+1]/max*height));
		}
		ofPopStyle();
	}
	
private:
	float _v1[TOTAL_VEL];
	float _v2[TOTAL_VEL];
	float _v3[TOTAL_VEL];
	float _v4[TOTAL_VEL];
	
	
	float max;
	
	int lastTime;
	
	
};
