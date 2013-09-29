
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
	box2d.createBounds(20, 20, width-40, height-40);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    m_game.setup(width, height, box2d.getWorld(), arduino);
    m_kinect.setup(width, height, box2d.getWorld());
    m_borda.setup();
    m_stats.setup();
    m_apoio.setup();
}

//--------------------------------------------------------------
void bicicletorama::update()
{   
	//arduino.update();
    m_game.update();
    m_kinect.update();
    m_borda.update(m_kinect.scaledImage);
    m_menu.update(m_game.playerList);
    m_apoio.update();
    box2d.update();
}

//--------------------------------------------------------------
void bicicletorama::draw() 
{
    m_game.draw();
    m_borda.draw();
    m_kinect.draw();
    m_menu.draw();
    m_apoio.draw();
    
	string info = "";
	info += "BICICLETORAMA v0.11\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n\n";
	ofSetHexColor(0xffffff);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void bicicletorama::keyPressed(int key)
{   
    m_kinect.keyPressed(key);
	
	if(key == 't') ofToggleFullscreen();
}


//--------------------------------------------------------------
void bicicletorama::keyReleased(int key) 
{   
    m_game.keyReleased(key);
}

//--------------------------------------------------------------
void bicicletorama::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void bicicletorama::mouseDragged(int x, int y, int button)
{
    m_game.mouseDragged(x, y, button);
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
    m_kinect.exit();
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
