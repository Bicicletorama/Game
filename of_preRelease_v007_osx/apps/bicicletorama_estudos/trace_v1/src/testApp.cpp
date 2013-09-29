#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	trail.allocate(1024, 768);
	
	pixels = new unsigned char[1024 * 768];
	for(int yy=0;yy<768;yy++){
		for(int xx=0;xx<1024;xx++){
			pixels[yy*1024 + xx] = 255;
		}	
	}
	
	trail.setFromPixels(pixels, 1024, 768);
	
	
	
	
	
	
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
	if(ofDist(mouseX, mouseY, oldX, oldY)>3){
		oldX = mouseX;
		oldY = mouseY;
		
		int loop = ofRandom(10);
		for(int i=0; i<loop; i++){
			int xx = mouseX + ofRandom(-5, 5);
			int yy = mouseY + ofRandom(-5, 5);
			if(xx > 0 && yy > 0){
				pixels[yy*1024 + xx] = 0;
			}
		}
	}
	trail.setFromPixels(pixels, 1024, 768);
}

//--------------------------------------------------------------
void testApp::draw(){
	trail.draw(0,0);
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
