#include "bicicletorama.h"

//--------------------------------------------------------------
void bicicletorama::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
}

//--------------------------------------------------------------
void bicicletorama::update() {
	box2d.update();	
}


//--------------------------------------------------------------
void bicicletorama::draw() {
	
	
	for(int i=0; i<obstaculos.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		obstaculos[i].draw();
	}
	
	for(int i=0; i<jogadores.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		jogadores[i].draw();
	}

	// draw the ground
	box2d.drawGround();
	
	
	
	string info = "";
	info += "Aperte [a] para adicionar obstaculo\n";
	info += "Aperte [p] para adicionar player\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	info += "k: "+ofToString(kk)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void bicicletorama::keyPressed(int key) {
	kk = key;
	
	if(key == 'a') {
		float w = ofRandom(4, 20);	
		float h = ofRandom(4, 20);	
		ofxBox2dRect rect;
		rect.setPhysics(3.0, 0.53, 0.1);
		rect.setup(box2d.getWorld(), mouseX, mouseY, w, h);
		obstaculos.push_back(rect);
	}
	
	if(key == 'p') {
		float w = 20;	
		float h = 20;	
		player p;
		p.setPhysics(3.0, 0.53, 0.1);
		p.setup(box2d.getWorld(), mouseX, mouseY, w, h);
		jogadores.push_back(p);
	}
	
	/*if(key == 'c') {
		float r = ofRandom(4, 20);		// a random radius 4px - 20px
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), mouseX, mouseY, r);
		circles.push_back(circle);
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);	
		float h = ofRandom(4, 20);	
		ofxBox2dRect rect;
		rect.setPhysics(3.0, 0.53, 0.1);
		rect.setup(box2d.getWorld(), mouseX, mouseY, w, h);
		boxes.push_back(rect);
	}*/
	
	if(key == 'f') ofToggleFullscreen();
	
	
	
	
	
	int force = 20;
	
	for(int i=0; i<jogadores.size(); i++) {
		ofVec2f p;
		p.set(jogadores[i].body->GetPosition().x, jogadores[i].body->GetPosition().y);
		p *= OFX_BOX2D_SCALE;
		
		if(key == 357){
			//vai pra cima
			jogadores[i].body->ApplyForce(b2Vec2(0, -force), jogadores[i].body->GetPosition());
		}
		if(key == 359){
			//vai pra baixo
			jogadores[i].body->ApplyForce(b2Vec2(0, force), jogadores[i].body->GetPosition());
		}
		if(key == 356){
			//vai pra esquerda
			jogadores[i].body->ApplyForce(b2Vec2(-force, 0), jogadores[i].body->GetPosition());
		}
		if(key == 358){
			//vai pra direita
			jogadores[i].body->ApplyForce(b2Vec2(force, 0), jogadores[i].body->GetPosition());
		}
	}
}

//--------------------------------------------------------------
void bicicletorama::keyReleased(int key) {
}

//--------------------------------------------------------------
void bicicletorama::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void bicicletorama::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void bicicletorama::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void bicicletorama::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void bicicletorama::resized(int w, int h){
}

