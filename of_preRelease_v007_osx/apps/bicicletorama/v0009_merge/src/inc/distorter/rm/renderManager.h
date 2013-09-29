#ifndef _RENDER_MANAGER_H
#define _RENDER_MANAGER_H

#include "ofTextureAdv.h"

class renderManager {
public:
	
	renderManager();
	void allocateForNScreens(int numScreens, int renderWidth, int renderHeight);
	void startOffscreenDraw();
	void endOffscreenDraw();
	void drawScreen(int nScreen);
	
	
	ofTextureAdv myOffscreenTexture;
	ofPoint ** outputPositions;
	ofPoint ** inputPositions;
	
	float ** compL;
	float ** compR;
	
	float width, height;
	float screenWidth, screenHeight;
	int nScreens;
};

#endif

