#include "bicicletorama.h"


//--------------------------------------------------------------
void bicicletorama::setup()
{
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    ofEnableAlphaBlending(); //TODO verificar se é melhor habilitar e desabilitar apenas para o render dos players ou deixar global
    
    //serial
//    arduino.connect("/dev/tty.usbmodemfa131", 57600);
    arduino.connect("/dev/tty.usbmodemfd121", 57600);
	ofAddListener(arduino.EInitialized, this, &bicicletorama::setupArduino);
    
	//box2d
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    //background
	background.loadImage("images/bicicletorama007.jpg");
       
    //players
    for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].setup(i, box2d.getWorld());
    }
    
    //start
    startGame();    
}

//--------------------------------------------------------------
void bicicletorama::update()
{   
	
    //box2d
	box2d.update();	
    
    //players
    for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].update();
    }
    
    //arduino
	arduino.update();
    
    float direction = arduino.getAnalog(3);
//    direction = ofMap(direction, 0, 1023, -1, 1);
    direction = ofMap(direction, 350, 670   , -1, 1);
    playerList[0].setDirection(-direction);
    
    float direction2 = arduino.getAnalog(1);
    direction2 = ofMap(direction2, 0, 1023, -1, 1);
    //playerList[1].setDirection(-direction2);
    
    //cout << direction << " - " << direction2 << endl;
}


//--------------------------------------------------------------
void bicicletorama::draw() 
{
    //background
    background.draw(0, 0);
    
    //players
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].draw();   
    }
    
    //hit
	for (int i=0; i<obstaculos.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		obstaculos[i].draw();
	}
	
	//debug
	string info = "";
	info += "BICICLETORAMA v0.5\n";
	info += "Aperte [o] para adicionar obstaculo\n";
	//info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	//info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0xffffff);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void bicicletorama::keyPressed(int key)
{   
	if(key == 'o') 
    {
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), mouseX, mouseY, 20);
        circle.body->SetType(b2_staticBody);
		obstaculos.push_back(circle);
	}
	
	if(key == 'f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void bicicletorama::keyReleased(int key) 
{    
    //players keyboards extra controls
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
void bicicletorama::mouseMoved(int x, int y ) {}

//--------------------------------------------------------------
void bicicletorama::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void bicicletorama::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void bicicletorama::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void bicicletorama::resized(int w, int h){}

//--------------------------------------------------------------
void bicicletorama::startGame()
{
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].goToStartPosition();
    }
}

//--------------------------------------------------------------
void bicicletorama::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &bicicletorama::setupArduino);
    
	// this is where you setup all the pins and pin modes, etc
	for (int i = 0; i < 13; i++){
		arduino.sendDigitalPinMode(i, ARD_OUTPUT);
	}
    
    //arduino.sendDigitalPinMode(13, ARD_OUTPUT);
    //arduino.sendDigitalPinMode(11, ARD_PWM);
//	arduino.sendAnalogPinReporting(0, ARD_ANALOG);
//    arduino.sendAnalogPinReporting(1, ARD_ANALOG);
    arduino.sendAnalogPinReporting(3, ARD_ANALOG);
    
}


