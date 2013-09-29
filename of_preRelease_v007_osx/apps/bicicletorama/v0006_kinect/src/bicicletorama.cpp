#include "bicicletorama.h"


//--------------------------------------------------------------
void bicicletorama::setup()
{
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    ofEnableAlphaBlending(); //TODO verificar se é melhor habilitar e desabilitar apenas para o render dos players ou deixar global
    
    //serial
    //arduino.connect("/dev/tty.usbmodemfa131", 57600);
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
    
    
    //Kinect + Triangle
	kinect.setRegistration( true );
    kinect.init();
	kinect.open( 0 );
	
	colorImg.allocate( kinect.width, kinect.height );
	grayImage.allocate( kinect.width, kinect.height );
	grayThreshNear.allocate( kinect.width, kinect.height );
	grayThreshFar.allocate( kinect.width, kinect.height );
    scaledImage.allocate( 800, 600);
	
	nearThreshold = 181;
	farThreshold = 121;
    
    debugKinect = false;
	
	//physics.init();
	//physics.createBounds();
	//physics.setGravity(0, 10);
	//physics.checkBounds(true);
    
    rm.init(800, 600 );
    
    //MAP
    mapAngle = 0;
    mapCenterX = .5;
    mapCenterY = .5;
    mapScaleX = 1;
    mapScaleY = 1;
    mapMoveX = 0;
    mapMoveY = 0;
}

//--------------------------------------------------------------
void bicicletorama::update()
{   
	
    
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
    
    updateKinect();
    
    box2d.update();

}

void bicicletorama::updateKinect() 
{
	kinect.update();
    
	if( kinect.isFrameNew() ) 
	{
		grayImage.setFromPixels( kinect.getDepthPixels(), kinect.width, kinect.height );
		
		grayThreshNear = grayImage;
		grayThreshFar = grayImage;
		grayThreshNear.threshold( nearThreshold, true );
		grayThreshFar.threshold( farThreshold );
		cvAnd( grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL );
		
		grayImage.flagImageChanged();
        
        
        
        grayImage.transform(mapAngle, mapCenterX, mapCenterY, mapScaleX, mapScaleY, mapMoveX, mapMoveY);
        
        //scaledImage.scaleIntoMe(grayImage);
		
		contourFinder.findContours( grayImage, 20, (800*600)/3, 5, false );
		
		triangle.clear();
		
        for ( int i = 0; i<contourFinder.nBlobs; i++ )
        {
			triangle.triangulate( contourFinder.blobs[i], max( 3.0f, (float)contourFinder.blobs[i].pts.size()/12) );
        }
		
		for ( int i = polys.size()-1; i >= 0; i--) { polys[i].destroy();}
		
		polys.clear();
		
		ofxTriangleData* tData;
		
		for ( int i = triangle.triangles.size()-1; i >= 0; i-- ) 
		{
			tData = &triangle.triangles[i];
			
			ofxBox2dPolygon poly;
			poly.addVertex(tData->a.x, tData->a.y);
			poly.addVertex(tData->b.x, tData->b.y);
			poly.addVertex(tData->c.x, tData->c.y);
			poly.create(box2d.getWorld());
			polys.push_back(poly);
		}
        
        cout << nearThreshold << farThreshold << endl;
	}	
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
    
    
    
    //Kinect + Triangle
    ofSetColor(255, 255, 255);
	
	//grayImage.draw(0, 0, kinect.getWidth(), kinect.getHeight());
    //
    
    if(debugKinect){
      grayImage.draw(0,0);  
      kinect.drawDepth(0,0, 200, 150);  
    }
    
    contourFinder.draw(0, 0);
	
    
	nbCircles = circles.size();
	for(int i=0; i<nbCircles; i++) circles[i].draw();
	
	//debug
	string info = "";
	info += "BICICLETORAMA v0.5\n";
	info += "Aperte [o] para adicionar obstaculo\n";
	info += "Near: "+ofToString(nearThreshold)+"\n";
	info += "Far: "+ofToString(farThreshold)+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n\n";
	info += "mapAngle: "+ofToString(mapAngle)+"\n";
	info += "mapCenterX: "+ofToString(mapCenterX)+"\n";
	info += "mapCenterY: "+ofToString(mapCenterY)+"\n";
	info += "mapScaleX: "+ofToString(mapScaleX)+"\n";
	info += "mapScaleY: "+ofToString(mapScaleY)+"\n";
	info += "mapMoveX: "+ofToString(mapMoveX)+"\n";
	info += "mapMoveY: "+ofToString(mapMoveY)+"\n";    
    
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
	
	if(key == 't') ofToggleFullscreen();

    
    //Kinect + Triangle
	switch (key) 
	{
		case '>':
			farThreshold ++;
			if (farThreshold > 255) farThreshold = 255;
			break;
			
		case '<':
			farThreshold --;
			if (farThreshold < 0) farThreshold = 0;
			break;
			
		case '+':
		case '=':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
			break;
			
		case '-':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
		case 'k':
            debugKinect = !debugKinect;
            break;
        /*case 'c':
			ofxBox2dCircle circle;
			circle.setPhysics(0.5, 0.53,10.1);
			circle.setup(box2d.getWorld(), mouseX, mouseY, 20);
			circles.push_back(circle);
			break;*/
        case 'a':
			mapAngle++;
			break;
        case 'z':
			mapAngle--;
			break;
        case 's':
			mapCenterX++;
			break;
        case 'x':
			mapCenterX--;
			break;
        case 'd':
			mapCenterY++;
			break;
        case 'c':
			mapCenterY--;
			break;
        case 'f':
			mapScaleX+=.1;
			break;
        case 'v':
			mapScaleX-=.1;
			break;
        case 'g':
			mapScaleY+=.1;
			break;
        case 'b':
			mapScaleY-=.1;
			break;
        case 'h':
			mapMoveX++;
			break;
        case 'n':
			mapMoveX--;
			break;
        case 'j':
			mapMoveY++;
			break;
        case 'm':
			mapMoveY--;
			break;
		
	}
}

void bicicletorama::exit() { kinect.close();}


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


