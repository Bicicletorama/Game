#include "bicicletorama.h"


//--------------------------------------------------------------
void bicicletorama::setup()
{
    ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
	
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].setup(box2d.getWorld(), i);   
    }
    
    startGame();    
}


//--------------------------------------------------------------
void bicicletorama::startGame()
{
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].start();
    }
}


//--------------------------------------------------------------
void bicicletorama::update()
{
	box2d.update();	
    
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].update();   
    }
}


//--------------------------------------------------------------
void bicicletorama::draw() 
{
	for(int i=0; i<obstaculos.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		obstaculos[i].draw();
	}
    
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].draw();   
    }

	// draw the ground
	box2d.drawGround();
	
	
	string info = "";
	info += "BICICLETORAMA v0.2\n";
	info += "Aperte [o] para adicionar obstaculo\n";
	info += "Aperte [p] para adicionar player\n";
	//info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	//info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	info += "k: "+ofToString(kk)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void bicicletorama::keyPressed(int key)
{
	kk = key;
    
	if(key == '1') startGame();
    
	if(key == 'o') {
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), mouseX, mouseY, 20);
        circle.body->SetType(b2_staticBody);
		obstaculos.push_back(circle);
	}
	
	if(key == 'f') ofToggleFullscreen();
	
    //players extra controls
    switch(key)
    { 
        case 357: playerList[0].applyImpulse(); break; //up
        case 359: playerList[0].setDirection(0); break; //down
        case 356: playerList[0].setDirectionIncrement(-1); break; //left
        case 358: playerList[0].setDirectionIncrement(1); break; //right
            
        case 119: playerList[1].applyImpulse(); break; //w
        case 115: playerList[1].setDirection(0); break; //s
        case 97 : playerList[1].setDirectionIncrement(-1); break; //a
        case 100: playerList[1].setDirectionIncrement(1); break;//d
            
        case 121: playerList[2].applyImpulse(); break; //y
        case 104: playerList[2].setDirection(0); break; //h
        case 103: playerList[2].setDirectionIncrement(-1); break; //g
        case 106: playerList[2].setDirectionIncrement(1); break; //j
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





