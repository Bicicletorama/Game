
#include "bicicletorama.h"


//--------------------------------------------------------------
void bicicletorama::setup()
{
    width = 1024;
    height = 768;
	
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_SILENT);//(OF_LOG_NOTICE);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds(20, 20, width-40, height-40-40);//40=altura do menu; 40=borda x 2
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    sound::setup();
    m_arduino.setup();
    m_game.setup(width, height, box2d.getWorld());
    m_kinect.setup(width, height, box2d.getWorld());
    m_borda.setup();
    m_menu.setup();
    m_panel.setup(&m_kinect, &m_arduino, &m_game);
}


//--------------------------------------------------------------
void bicicletorama::update()
{   
	m_arduino.update();
    m_game.update(m_arduino.guidao, m_arduino.velo);
    m_kinect.update();
    m_borda.update(m_kinect.scaledImage);
    m_menu.update(m_game.playerList);
    box2d.update();
}

//--------------------------------------------------------------
void bicicletorama::draw() 
{
    m_game.draw();
    m_borda.draw();
    m_kinect.draw();
    m_menu.draw();
 
    /*
	string info = "";
	info += "BICICLETORAMA v0.13\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n\n";
	ofSetHexColor(0xffffff);
	ofDrawBitmapString(info, 30, 30);
     */
}

//--------------------------------------------------------------
void bicicletorama::keyPressed(int key)
{   
    
    m_kinect.keyPressed(key);
    m_panel.keyPressed(key);
	
	if(key == 't') ofToggleFullscreen();
	if(key == 'f') ofToggleFullscreen();
    
}


//--------------------------------------------------------------
void bicicletorama::keyReleased(int key) 
{   
    m_game.keyReleased(key);
    m_menu.keyReleased(key);
}

//--------------------------------------------------------------
void bicicletorama::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void bicicletorama::mouseDragged(int x, int y, int button)
{//
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
    m_arduino.exit();
}
