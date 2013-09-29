#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	velocidades.setup();

}

//--------------------------------------------------------------
void testApp::update(){
	velocidades.addValues(mouseX, mouseY, ofRandom(mouseX), ofRandom(mouseY));
}

//--------------------------------------------------------------
void testApp::draw(){
	velocidades.draw(30, 30);
	
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