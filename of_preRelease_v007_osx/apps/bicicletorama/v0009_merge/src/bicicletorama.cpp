#include "bicicletorama.h"


//--------------------------------------------------------------
void bicicletorama::setup()
{
    width = 1024;
    height = 768;
    
	showRawKinect = false;
	
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(30);
    ofEnableAlphaBlending(); //TODO verificar se é melhor habilitar e desabilitar apenas para o render dos players ou deixar global
    
    //serial
    arduino.connect("/dev/tty.usbmodemfd121", 57600);
    //arduino.connect("/dev/tty.usbmodemfa131", 57600);
    arduino.setDigitalHistoryLength(10);
	ofAddListener(arduino.EInitialized, this, &bicicletorama::setupArduino);
    
	
	
	//crop::
	quadCropCorners.reserve(4);
	
	
	quadCropCorners.push_back( ofPoint(50,10 ));
	quadCropCorners.push_back( ofPoint(400,10) );
	quadCropCorners.push_back( ofPoint(400,300) );
	quadCropCorners.push_back( ofPoint(50, 300) );
	
	
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
	grayImage2.allocate( kinect.width, kinect.height );
	grayThreshNear.allocate( kinect.width, kinect.height );
	grayThreshFar.allocate( kinect.width, kinect.height );
    scaledImage.allocate( width, height);
	
	kinectOutputCropped.allocate(kinect.width,kinect.height );
	kinectOutputCropped2.allocate(kinect.width,kinect.height );
	
	nearThreshold = 34;
	farThreshold = 30;
	
	
	blur = 0;
    
    debugKinect = false;
	
	useRegCam = true;
	
	if ( useRegCam )
	{
		vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);	
	}
	
	//physics.init();
	//physics.createBounds();
	//physics.setGravity(0, 10);
	//physics.checkBounds(true);
    
    //rm.init(800, 600 );
    
    //MAP
    mapAngle = 0;
    mapCenterX = .5;
    mapCenterY = .5;
    mapScaleX = 1;
    mapScaleY = 1;
    mapMoveX = 0;
    mapMoveY = 0;
	
	minBlobSize = 0;
	maxBlobSize = 0;
    
    //TRACE
	canvas.allocate(width, height, GL_RGBA);
    
	
	canvas.begin();  
	ofClear(255, 255, 255, 0);  
    canvas.end();	
	
	//UI
	setGUI1(); 
	setGUI2();
	
	gui1->loadSettings("GUI/settings.xml");
	gui1->setVisible(false);
	
	gui2->loadSettings("GUI/crop.xml");
	gui2->setVisible(false);
}

//--------------------------------------------------------------
void bicicletorama::update()
{   
    //contagem regressiva
    if (timerStartGame > 0) {
        timerStartGame--;
    } else if (timerStartGame == 0) {
        for (int i=0; i<TOTAL_PLAYERS; i++) {
            playerList[i].locked = false;
        }        
    }
	
    //arduino
	arduino.update();
    
    //players
    for (int i=0; i<TOTAL_PLAYERS; i++) {
        //        playerList[i].update(arduino.getAnalog(i), arduino.getDigital(i+2));
    }
    playerList[0].update(0, 0, false);
    playerList[1].update(0, 0, false);
    playerList[2].update(0, 0, false);
    playerList[3].update(arduino.getAnalog(0), arduino.getDigital(2), true);
    
    cout << arduino.getAnalog(0) << " - " << arduino.getDigital(2) << endl;
    
    list<int>* lista = arduino.getDigitalHistory(2);
    for (list<int>::iterator it = lista->begin(); it != lista->end(); it++) {
        //cout << *it << " ";
    }
//    cout << endl;
    
    
    
    updateKinect();
    
    box2d.update();
}

void bicicletorama::updateKinect() 
{
	kinect.update();
    
	
	if( kinect.isFrameNew() ) 
	{
		
		
		grayImage.setFromPixels( kinect.getDepthPixels(), kinect.width, kinect.height );
		
		grayImage2.setFromPixels( kinect.getPixels(), kinect.width, kinect.height );
			
		getQuadSubImage(&grayImage, &kinectOutputCropped, &quadCropCorners, 1);
		
		getQuadSubImage(&grayImage, &kinectOutputCropped2, &quadCropCorners, 1);

		

				
		kinectOutputCropped.blur(blur);
			
		
		grayThreshNear = kinectOutputCropped;
		grayThreshFar = kinectOutputCropped;
		grayThreshNear.threshold( nearThreshold, true );
		grayThreshFar.threshold( farThreshold );
		cvAnd( grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), kinectOutputCropped.getCvImage(), NULL );
		
		kinectOutputCropped.flagImageChanged();
        
        //kinectOutputCropped.transform(mapAngle, mapCenterX, mapCenterY, mapScaleX, mapScaleY, mapMoveX, mapMoveY);
        
        scaledImage.scaleIntoMe(kinectOutputCropped);
		
		contourFinder.findContours( scaledImage, minBlobSize, maxBlobSize, 20, false );
		
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
    
    //trace
    background.draw(0, 0);
	canvas.begin();
	{
        
        ofSetColor(255,255,255,3);
        background.draw(0, 0);
        
        
        for (int i=0; i<TOTAL_PLAYERS; i++) {
            int xx = playerList[i].x;
            int yy = playerList[i].y;
            ofSetColor(playerList[i].color, 255);
            if(ofDist(xx, yy, playerList[i].oldX, playerList[i].oldY)>1){
                
                int loop = ofRandom(10,30);
                for(int j=0; j<loop; j++){
                    int xx2 = xx + ofRandom(-5, 5);
                    int yy2 = yy + ofRandom(-5, 5);
                    if(xx2 > 0 && yy2 > 0){
                        ofCircle(xx2, yy2, 1);
                    }
                }
            }
        }
		
	}
	canvas.end();
	canvas.draw(0,0);
    
    
    //players
    ofSetColor(255);
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
	
	//kinectOutputCropped2.draw(0, 0,400, 300);
    
    if(debugKinect){
      kinectOutputCropped.draw(0,0, width, height);  
       
    }
	
	if ( showRawKinect )
	{
		kinect.drawDepth(606,500, 200, 150); 
	}
    
    contourFinder.draw(0, 0, width, height);
	
	//triangle.draw( width, 0 );
	
    
	nbCircles = circles.size();
	for(int i=0; i<nbCircles; i++) circles[i].draw();
	
	//debug
	string info = "";
	info += "BICICLETORAMA v0.9\n";
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
	info += "min: "+ofToString(minBlobSize)+"\n"; 
	info += "max: "+ofToString(maxBlobSize)+"\n"; 
    
	//ofSetHexColor(0xffffff);
	//ofDrawBitmapString(info, 30, 30);
    
    //contagem regressiva
    if (timerStartGame > 0) {
        string contagem = ofToString(timerStartGame/60 + 1);
        int scale = 60;
        ofPushStyle();
        ofPushMatrix();
        ofSetHexColor(0xffffff);
        ofScale(scale, scale);
        ofDrawBitmapString(contagem, 450/scale, 700/scale);
        ofPopMatrix();
        ofPopStyle();
    }
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
		case 'k':
            debugKinect = !debugKinect;
            break;
		case 'l':
            showRawKinect = !showRawKinect;
            break;
		case ' ':
            gui1->toggleVisible();
            gui2->toggleVisible();
            break;	
		case 's':
			save();
			break;		
			
			
        /*case 'c':
			ofxBox2dCircle circle;
			circle.setPhysics(0.5, 0.53,10.1);
			circle.setup(box2d.getWorld(), mouseX, mouseY, 20);
			circles.push_back(circle);
			break;*/	
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
            
        case 'p': startGame(); break;
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
        playerList[i].goToStartPosition(true);
    }
    
    timerStartGame = 3 * 60;
    
    canvas.begin();
        ofClear(0, 0, 0);
    canvas.end();
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


//--------------------------------------------------------------
void bicicletorama::setGUI1()
{
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 455-xInit; 
	
	gui1 = new ofxUICanvas(0, 0, length+xInit, ofGetHeight()); 
	gui1->addWidgetDown(new ofxUILabel("BICICLETORAMA", OFX_UI_FONT_LARGE)); 
    gui1->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_MEDIUM)); 
	
    gui1->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
	gui1->addWidgetDown(new ofxUILabel("MAPPING", OFX_UI_FONT_MEDIUM)); 
	gui1->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 100.0, 50, "Blur")); 	 
	gui1->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 200000.0, 50.0, 100.0, "BlobSize")); 
	gui1->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, nearThreshold, farThreshold, "FarNear")); 	
    
	gui1->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
	gui1->addWidgetDown(new ofxUILabelButton( length-xInit, false, "SAVE", OFX_UI_FONT_MEDIUM)); 	
	gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "Align Right")); 	
    
	
	
    
    ofAddListener(gui1->newGUIEvent,this,&bicicletorama::guiEvent);
}

//--------------------------------------------------------------
void bicicletorama::setGUI2()
{
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	
	gui2 = new ofxUICanvas(465+xInit, 0, length+xInit, ofGetHeight()); 
	gui2->addWidgetDown(new ofxUILabel("CROP", OFX_UI_FONT_MEDIUM)); 
    
	gui2->addWidgetDown(new ofxUI2DPad(length-xInit,120, ofPoint(0,640),  ofPoint(0,480), ofPoint(quadCropCorners[0].x, quadCropCorners[0].y), "TOP_RIGHT"));
	gui2->addWidgetDown(new ofxUI2DPad(length-xInit,120, ofPoint(0,640),  ofPoint(0,480), ofPoint(quadCropCorners[3].x, quadCropCorners[3].y), "BOTTOM_LEFT"));
    
    ofAddListener(gui2->newGUIEvent,this,&bicicletorama::guiEvent);
}


//--------------------------------------------------------------
void bicicletorama::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	cout << "got event from: " << name << endl; 	
	
	if(name == "Blur")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blur = slider->getScaledValue(); 
	}
	else if(name == "BlobSize")
	{
		ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget; 
		minBlobSize = slider->getScaledValueLow(); 
		maxBlobSize = slider->getScaledValueHigh(); 
	}
	else if(name == "FarNear")
	{
		ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget; 
		farThreshold = slider->getScaledValueLow(); 
		nearThreshold = slider->getScaledValueHigh(); 
	}
	else if(name == "SAVE")
	{
		save();
	}
	else if(name == "Align Right")
	{
		/*ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
		if(toggle->getValue()){
			gui2->rect->x = ofGetWidth() - gui2->rect->width - OFX_UI_GLOBAL_WIDGET_SPACING;
			gui1->rect->x = gui2->rect->x - gui1->rect->width - OFX_UI_GLOBAL_WIDGET_SPACING;
		}else{
			gui1->rect->x = OFX_UI_GLOBAL_WIDGET_SPACING;
			gui2->rect->x = gui1->rect->x + gui1->rect->width + OFX_UI_GLOBAL_WIDGET_SPACING;
		}*/
	}
	else if(name == "TOP_RIGHT")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
		quadCropCorners[0].x = pad->getScaledValue().x;
		quadCropCorners[0].y = pad->getScaledValue().y;
		
		quadCropCorners[1].y = pad->getScaledValue().y;
		quadCropCorners[3].x = pad->getScaledValue().x;
	}
	else if(name == "BOTTOM_LEFT")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
		quadCropCorners[2].x = pad->getScaledValue().x;
		quadCropCorners[2].y = pad->getScaledValue().y;
		
		quadCropCorners[1].x = pad->getScaledValue().x;
		quadCropCorners[3].y = pad->getScaledValue().y;
	}
	
	
	
	
}

void bicicletorama::save()
{
	gui1->saveSettings("GUI/settings.xml");
	gui2->saveSettings("GUI/crop.xml");
}




