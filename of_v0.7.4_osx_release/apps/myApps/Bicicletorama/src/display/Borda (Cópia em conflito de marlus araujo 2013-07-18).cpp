#include "Borda.h"

void Borda::setup(ofxCvContourFinder * _contourFinder)
{
    contourFinder = _contourFinder;
    
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
}

void Borda::update()
{
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

void Borda::draw()
{
    ofPushStyle();
    
    
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ZERO);
    
    //empty area
    ofSetColor(0,0,0,0);
    ofRect(border, border, mask.getWidth() -border -border, mask.getHeight() -border -border);
    
    //blobs area
    ofSetColor(255,255,255,255);
    for (int i = 0; i < contourFinder->blobs.size(); i++) {
        ofBeginShape();
        for (int j = 0; j < contourFinder->blobs[i].pts.size(); j++){
            ofVertex(contourFinder->blobs[i].pts[j].x, contourFinder->blobs[i].pts[j].y);
        }
        ofEndShape(true);
    }
    
    
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


