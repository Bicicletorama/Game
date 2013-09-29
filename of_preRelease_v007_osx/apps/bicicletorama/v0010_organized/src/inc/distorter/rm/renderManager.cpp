

#include "renderManager.h"
#include "ofTextureAdv.h"

//---------------------------------------------------------------------------
renderManager::renderManager()
{
   
}

void renderManager::allocateForNScreens(int numScreens, int renderWidth, int renderHeight){
    width   = renderWidth;
    height  = renderHeight;
	
    screenWidth  = (float)width / (float)numScreens;
    screenHeight = height;
	
	myOffscreenTexture.allocate(renderWidth, renderHeight);
	
	
    nScreens            = numScreens;
    outputPositions     = new ofPoint*[nScreens];
    inputPositions      = new ofPoint*[nScreens];
	
    compL               = new float*[nScreens];
    compR               = new float*[nScreens];
	
    float w_d_3 = (float)width / (float)nScreens;
    float inner_d_3 = 1.0f / (float)nScreens;
    for (int i = 0; i < nScreens; i++){
		
        inputPositions[i]  = new ofPoint[4];
        outputPositions[i] = new ofPoint[4];
		
        //-----------------------------------------
        outputPositions[i][0].set(w_d_3*(i),0,0);
        outputPositions[i][1].set(w_d_3*(i+1),0,0);
        outputPositions[i][2].set(w_d_3*(i+1),height,0);
        outputPositions[i][3].set(w_d_3*(i),height,0);
		
        inputPositions[i][0].set(inner_d_3*(i),0,0);
        inputPositions[i][1].set(inner_d_3*(i+1),0,0);
        inputPositions[i][2].set(inner_d_3*(i+1),1,0);
        inputPositions[i][3].set(inner_d_3*(i),1,0);
		
        compL[i] = new float[GRID_Y];
        compR[i] = new float[GRID_Y];
		
        memset(compL[i], 0, sizeof(float) * GRID_Y);
        memset(compR[i], 0, sizeof(float) * GRID_Y);
    }
}


void renderManager::startOffscreenDraw(){
    if( nScreens <= 0 ) return;
	
  	myOffscreenTexture.swapIn();
	
    myOffscreenTexture.setupScreenForMe();
}

//---------------------------------------------------------------------------
void renderManager::endOffscreenDraw(){
    if( nScreens <= 0 ) return;
	
    myOffscreenTexture.swapOut();
    myOffscreenTexture.setupScreenForThem();
}

void renderManager::drawScreen(int nScreen){
    if( nScreens <= 0 ) return;
	
    myOffscreenTexture.setLeftComp(compL[nScreen]);
    myOffscreenTexture.setRightComp(compR[nScreen]);
    myOffscreenTexture.setPoints(inputPositions[nScreen], outputPositions[nScreen]);
    myOffscreenTexture.draw();
}


