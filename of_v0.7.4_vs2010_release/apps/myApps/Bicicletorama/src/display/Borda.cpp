#include "Borda.h"

void Borda::setup(ofxCvContourFinder * _contourFinder)
{
    contourFinder = _contourFinder;
    
    border = 20;
        
    mask.loadImage("images/border_mask.png");

	bg.loadMovie("videos/bg.mov");
	bg.setLoopState(OF_LOOP_NORMAL);
	bg.play();
}

void Borda::update()
{
	bg.update();
}

void Borda::draw()
{
    ofPushStyle();
    
    
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ZERO);
    
    //empty area
    ofSetColor(0,0,0,0);
    ofRect(border, border, mask.getWidth() - border - border, mask.getHeight() - border - border);
    
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
    
    
    ofSetColor(255,255,255,255);
    bg.draw(0, 0, WIDTH, HEIGHT);
    
    glDisable(GL_BLEND);
    
    
    ofPopStyle();
}


