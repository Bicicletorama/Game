#ifndef _IMAGE_TEXTURE_ADV_H_
#define _IMAGE_TEXTURE_ADV_H_

#include "ofMain.h"
#include "ofxFBOTexture.h"

#define GRID_X 12
#define GRID_Y 8



class ofTextureAdv : public ofxFBOTexture {

	public :
		ofTextureAdv();
		~ofTextureAdv();
		//void allocate(int w, int h, int internalGlDataType = GL_RGBA, int numSamples = 0);
		void allocate(int w, int h, int internalGlDataType = GL_RGBA, int numSamples = 0){ ofxFBOTexture::allocate(w,h, internalGlDataType, numSamples);   };
		
		void clear();
		void loadData(unsigned char * data, int w, int h, int glDataType);
		void setPoints(ofPoint pts[4]);
		void setPoints(ofPoint inputPts[4], ofPoint outputPts[4]);
		void draw(bool showGrid = false);
		void draw(float x, float y) { ofTexture::draw(x,y); };
		void draw(float x, float y, float w, float h) { ofTexture::draw(x,y,w,h); };
	
		void setLeftComp(float * compPts){
			for(int i =0;  i < GRID_Y; i++){
				compL[i] = compPts[i];
			}
		}
	
		void setRightComp(float * compPts){
			for(int i =0;  i < GRID_Y; i++){
				compR[i] = compPts[i];
			}
		}
	
		int width, height;
	
	protected:
	
		void updatePoints();
		
		ofPoint quad[4];
		ofPoint utQuad[4];
	
		float * compL;
		float * compR;
	
		ofPoint * grid;
		ofPoint * coor;
		
};

#endif
