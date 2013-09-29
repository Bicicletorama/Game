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

class Borda{
	
public:
	
	ofImage *image1;
	
	void setup(){
		//files.allowExt("jpg");
		//files.allowExt("png");
		//files.listDir("texturas/");

		
		//string path1 = files.getPath(ofRandom(files.numFiles()));
		string path1 = "imagem.png";
		
		image1 = new ofImage();
		image1->allocate(260,260,OF_IMAGE_COLOR);
		//image1->loadImage(path1);
		
	}
	
	void update(){
		
	}
	
	void draw(){
		image1->draw(0,0);
	}
	
private:
	queue<string> pathsToLoad;
	string paths[2];
    string names[2];
    bool bFrameNew[2];
    ofPixels * pixels[2];
    ofTexture textures[2];
    ofImage images[2];
	
	
	ofDirectory files;
	
	
};
