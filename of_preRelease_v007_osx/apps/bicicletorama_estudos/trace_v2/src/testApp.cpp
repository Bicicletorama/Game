#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30);
	
    ofEnableAlphaBlending(); 
    
    //ofBackground(0,0,0);
    //ofBackground(255,255,255);
	
	//cout << checkGLSupport() << endl;
	
	canvas.allocate(1024, 768, GL_RGBA);

	
	canvas.begin();  
	ofClear(255, 255, 255, 0);  
    canvas.end();
    
    bg.loadImage("bicicletorama007.jpg");
	
	oldX = 0;
	oldY = 0;

	
	
	blur.setup(canvas.getWidth(), canvas.getHeight(), 4, .2, 4);
	
	
	
	/*trace.allocate(1024, 768);
	
	colorPixels = new unsigned char[1024 * 768 * 4];
	for(int yy=0;yy<768 * 4;yy++){
		for(int xx=0;xx<1024 * 4;xx++){
			colorPixels[yy*1024 + xx] = 255;
		}	
	}
	
	trace.setFromPixels(colorPixels, 1024, 768);*/
	
	
	
	
	
	oldX = 0;
	oldY = 0;

}

//--------------------------------------------------------------
void testApp::update(){
	//blur.setScale(ofMap(mouseX, 0, ofGetWidth(), 1, 4));
	//blur.setRotation(ofMap(mouseY, 0, ofGetHeight(), -PI, PI));
}


//--------------------------------------------------------------
void testApp::draw(){
    
    bg.draw(0,0,1024, 768);
	canvas.begin();
	{
        
        ofSetColor(255,255,255,3);
        bg.draw(0,0,1024, 768);
        
        ofSetColor(255, 255, 255, 255);
		if(ofDist(mouseX, mouseY, oldX, oldY)>1){
			
			int loop = ofRandom(10,30);
			for(int i=0; i<loop; i++){
				int xx = mouseX + ofRandom(-5, 5);
				int yy = mouseY + ofRandom(-5, 5);
				if(xx > 0 && yy > 0){
					ofCircle(xx, yy, 1);
				}
			}
            ofLine(mouseX, mouseY, oldX, oldY);
            
            oldX = mouseX;
            oldY = mouseY;
		}
	}
	canvas.end();
	canvas.draw(0,0,1024,768);
	
    /*ofBackground(0);
    
    blur.begin();
	ofSetColor(255);
	canvas.draw(0,0,1024,768);
	blur.end();
    
	blur.draw();
    
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
