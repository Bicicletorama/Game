#include "bicicletorama.h"


//--------------------------------------------------------------
void Bicicletorama::setup()
{
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_SILENT);//(OF_LOG_NOTICE);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds(20, 20, WIDTH-40, HEIGHT-40-40);//40=altura do menu; 40=borda x 2
	box2d.setFPS(30.0);
	box2d.registerGrabbing();

	Tweenzor::init();
    
    sound::setup();
    
    arduino.setup();
    kinect.setup(box2d.getWorld());
    game.setup(&box2d, &arduino);
    borda.setup(&kinect.contourFinder);
    menu.setup();
    m_panel.setup(&kinect, &game);
}


//--------------------------------------------------------------
void Bicicletorama::update()
{
    arduino.update();
    kinect.update();
	Tweenzor::update( ofGetElapsedTimeMillis() );
    game.update();
    borda.update();
    menu.update(game.playerList);
    box2d.update();
}

//--------------------------------------------------------------
void Bicicletorama::draw() 
{
    game.draw();
    borda.draw();
    kinect.draw();
    menu.draw();
}

//--------------------------------------------------------------
void Bicicletorama::keyPressed(int key)
{   
    kinect.keyPressed(key);
    m_panel.keyPressed(key);
	
	if (key == 'f') ofToggleFullscreen();
}


//--------------------------------------------------------------
void Bicicletorama::keyReleased(int key) 
{   
    game.keyReleased(key);
    menu.keyReleased(key);
}

//--------------------------------------------------------------
void Bicicletorama::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void Bicicletorama::mouseDragged(int x, int y, int button)
{
    game.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void Bicicletorama::mousePressed(int x, int y, int button) {
    game.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void Bicicletorama::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void Bicicletorama::resized(int w, int h) {}

//--------------------------------------------------------------
void Bicicletorama::exit()
{
    arduino.close();
    kinect.exit();
	Tweenzor::destroy();
}
