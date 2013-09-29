
#include "bicicletorama.h"


//--------------------------------------------------------------
void bicicletorama::setup()
{
    width = 1024;
    height = 768;
	
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
    arduino.connect("/dev/tty.usbmodemfd121", 57600);
    //arduino.connect("/dev/tty.usbmodemfa131", 57600);
    arduino.setDigitalHistoryLength(10);
	ofAddListener(arduino.EInitialized, this, &bicicletorama::setupArduino);
    		
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    game.setup(width, height, box2d.getWorld(), arduino);
    
    scenario.setup(width, height, box2d.getWorld());
}

//--------------------------------------------------------------
void bicicletorama::update()
{   
	arduino.update();
    
    game.update();
    
    scenario.update();
    
    box2d.update();
}

//--------------------------------------------------------------
void bicicletorama::draw() 
{
    game.draw();
    
    scenario.draw();

	string info = "";
	info += "BICICLETORAMA v0.10\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n\n";
	ofSetHexColor(0xffffff);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void bicicletorama::keyPressed(int key)
{   
    scenario.keyPressed(key);
	
	if(key == 't') ofToggleFullscreen();
}


//--------------------------------------------------------------
void bicicletorama::keyReleased(int key) 
{   
    game.keyReleased(key);
}

//--------------------------------------------------------------
void bicicletorama::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void bicicletorama::mouseDragged(int x, int y, int button)
{
    game.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void bicicletorama::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void bicicletorama::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void bicicletorama::resized(int w, int h) {}

//--------------------------------------------------------------
void bicicletorama::exit()
{ 
    scenario.exit();
}

//--------------------------------------------------------------
void bicicletorama::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &bicicletorama::setupArduino);
    
	// this is where you setup all the pins and pin modes, etc
	for (int i = 0; i < TOTAL_PLAYERS; i++){
        arduino.sendDigitalPinMode(i+2, ARD_INPUT);
        arduino.sendAnalogPinReporting(i, ARD_ANALOG);
	}
}
