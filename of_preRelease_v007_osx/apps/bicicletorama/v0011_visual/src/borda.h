//
//  Borda.h
//  bicicletorama
//
//  Created by Vamoss on 18/06/12.
//  Copyright 2012 Bicicletorama. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxCvImage.h"

class borda {
    
public:
    
    void setup(){
        border = 20;
        
        changeInterval = 10000;
        lastTime = -10000;
        
        margin = -500;
        
        ofDirectory dir;
        dir.allowExt("jpg");
        dir.allowExt("png");
        
        int nFiles = dir.listDir("texturas");
        if(nFiles) {
            
            for(int i=0; i<dir.numFiles(); i++) { 
                string filePath = dir.getPath(i);
                images.push_back(ofImage());
                images.back().loadImage(filePath);
            }
            
        } 
        
        curImage = 0;
        
        
        mask.loadImage("images/border_mask.png");
        
        finalImageMask.allocate(mask.getWidth(), mask.getHeight(), GL_RGBA);
        
        
    }
    
    void update(ofxCvGrayscaleImage newMask){
        
        
        //UPDATE MASK
        /*finalImageMask.begin();
         ofClear(0,0,0,0);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
         mask.draw(0,0,mask.getWidth(), mask.getHeight());
         newMask.draw(0,0,mask.getWidth(), mask.getHeight());
         finalImageMask.end();*/
        
        int ww = mask.getWidth();
        int hh = mask.getHeight();
        
        unsigned char* newPixels = newMask.getPixels();
        unsigned char* pixels  = new unsigned char[ww * hh * 4];
        //memcpy(mask.getPixels(), pixels, ww * hh * 4);
        
        
        int pos;
        for(int x=0; x<ww; x++){
            for(int y=0; y<hh; y++){
                pos = y * ww + x;
                if(newPixels[pos]==255 || x < border || y < border || x > ww - border || y > hh - border){
                    pixels[pos*4+0] = 255;
                    pixels[pos*4+1] = 255;
                    pixels[pos*4+2] = 255;
                    pixels[pos*4+3] = 255;
                }else{
                    pixels[pos*4+0] = 0;
                    pixels[pos*4+1] = 0;
                    pixels[pos*4+2] = 0;
                    pixels[pos*4+3] = 0;
                }
                
            }
        }
        
        finalMask.setFromPixels(pixels, ww, hh, OF_IMAGE_COLOR_ALPHA);
        
        delete pixels;
        
        
        //CHECK CHANGE IMAGE
        if(ofGetElapsedTimeMillis()-lastTime>changeInterval){
            lastTime = ofGetElapsedTimeMillis();
            
            curImage++;
            if(curImage>images.size()-1){
                curImage=0;
            }
            translate.x = 0;
            translate.y = 0;
        }
        
        
        //TRANSLATE
        translate.x+=0.8;
        translate.y+=0.8;
    }
    
    void draw(){
        
        
        ofPushStyle();
        
        
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ZERO);
        
        ofSetColor(255,255,255,255);
        //finalImageMask.draw(0,0);

        finalMask.draw(0,0);
        //mask.draw(0,0);
        
        glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
        
        int curX;
        int curY;
        
        ofSetColor(255,255,255,255);
        curX = margin+translate.x;
        curY = margin+translate.y;
        
        for(int x=curX; x<ofGetWidth()-margin; x+=images[curImage].getWidth()){
            for(int y=curY; y<ofGetWidth()-margin; y+=images[curImage].getHeight()){
                images[curImage].draw(x,y);
            }
        }
        
        glDisable(GL_BLEND);
        
        
        ofPopStyle();
    }
    
    
private:
    vector <ofImage> images;
    
    int changeInterval;
    int lastTime;
    
    int margin;
    
    ofPoint translate;
    
    int curImage;
    
    ofImage mask;
    unsigned char* maskPixels;
    
    int border;
    
    ofImage finalMask;
    ofFbo finalImageMask;
};