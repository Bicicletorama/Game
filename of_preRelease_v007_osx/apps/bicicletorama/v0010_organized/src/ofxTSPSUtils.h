//
//  ofxTSPSUtils.h
//  openTSPS
//
//  Created by brenfer on 11/11/11.
//  Copyright 2011 Rockwell Group. All rights reserved.
//

#include "ofxOpenCv.h"

// useful! from http://forum.openframeworks.cc/index.php/topic,6398.0.html
static void getQuadSubImage(ofxCvImage * inputImage, ofxCvGrayscaleImage * outputImage, vector <ofPoint> * quad, int bpp) {
    unsigned char * inpix;
    unsigned char * outpix;
    inpix   = inputImage->getPixels();
    outpix  = outputImage->getPixels();
    
    int inW, inH, outW, outH;
    inW = inputImage->width;
    inH = inputImage->height;
    outW = outputImage->width;
    outH = outputImage->height;
    
    for(int x=0;x<outW;x++) {
        for(int y=0;y<outH;y++) {
            float xlrp = x/(float)outW;
            float ylrp = y/(float)outH;
            int xinput = ((*quad)[0].x*(1-xlrp)+(*quad)[1].x*xlrp)*(1-ylrp) + ((*quad)[3].x*(1-xlrp)+(*quad)[2].x*xlrp)*ylrp;
            int yinput = ((*quad)[0].y*(1-ylrp)+(*quad)[3].y*ylrp)*(1-xlrp) + ((*quad)[1].y*(1-ylrp)+(*quad)[2].y*ylrp)*xlrp;
            int inIndex = (xinput + yinput*inW)*bpp;
            int outIndex = (x+y*outW)*bpp;
            memcpy((void*)(outpix+outIndex),(void*)(inpix+inIndex),sizeof(unsigned char)*bpp);
        }
    }
    outputImage->setFromPixels(outpix, outW, outH);
}

//static void setPointsInVector( vector <ofPoint> * vec, int item );
static void setPointsInVector( vector <ofPoint> * quad, int item, int cuts )
{
	int w = 640;
	int h = 480;
	
	
	(*quad).push_back(  ofPoint(0,item*(h/cuts)));
	(*quad).push_back(  ofPoint(w,item*(h/cuts)));
	(*quad).push_back(  ofPoint(w,(item+1)*(h/cuts)));
	(*quad).push_back(  ofPoint(0, (item+1)*(h/cuts)));
	 
	 
}