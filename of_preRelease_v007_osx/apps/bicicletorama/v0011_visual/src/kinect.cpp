
#include "kinect.h"


void kinect::setup(int _width, int _height, b2World* _world)
{
    width = _width;
    height = _height;
    world = _world;
    
	showRawKinect = false;
    
	//crop::
	quadCropCorners.reserve(4);
	
	
	quadCropCorners.push_back( ofPoint(50,10 ));
	quadCropCorners.push_back( ofPoint(400,10) );
	quadCropCorners.push_back( ofPoint(400,300) );
	quadCropCorners.push_back( ofPoint(50, 300) );
    
    
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
    minBlobSize = 0;
	maxBlobSize = 0;	
	
	//UI
	setGUI1(); 
	setGUI2();
	
	gui1->loadSettings("GUI/settings.xml");
	gui1->setVisible(false);
	
	gui2->loadSettings("GUI/crop.xml");
	gui2->setVisible(false);
    
}

void kinect::update()
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
			poly.create(world);
			polys.push_back(poly);
		}
        
        cout << nearThreshold << farThreshold << endl;
	}	
    
}

void kinect::draw()
{
    
    ofSetColor(255, 255, 255);
	
	//grayImage.draw(0, 0, kinect.getWidth(), kinect.getHeight());
	
	//kinectOutputCropped2.draw(0, 0,400, 300);
    
    if (showCropped)    kinectOutputCropped2.draw(0,0, width, height);  
	if (debugKinect)    scaledImage.draw(0,0, width, height);  
	if (showRawKinect)  kinect.drawDepth(606,500, 200, 150); 
	if (showContour)    contourFinder.draw(0, 0, width, height);
	
	//triangle.draw( width, 0 );
    
    
    
	nbCircles = circles.size();
	for(int i=0; i<nbCircles; i++) circles[i].draw();
    
	
	//debug
	string info = "";
	info += "Near: "+ofToString(nearThreshold)+"\n";
	info += "Far: "+ofToString(farThreshold)+"\n\n";
	info += "min: "+ofToString(minBlobSize)+"\n"; 
	info += "max: "+ofToString(maxBlobSize)+"\n";
    
	//ofSetHexColor(0xffffff);
	//ofDrawBitmapString(info, 30, 30);     

}

void kinect::keyPressed(int key)
{   
	switch (key) 
	{
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
             circle.setup(world, mouseX, mouseY, 20);
             circles.push_back(circle);
             break;*/
	}
}

//--------------------------------------------------------------
void kinect::setGUI1()
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
	gui1->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 2000000.0, 50.0, 100.0, "BlobSize")); 
	gui1->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, nearThreshold, farThreshold, "FarNear")); 	
    
	gui1->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
	gui1->addWidgetDown(new ofxUILabelButton( length-xInit, false, "SAVE", OFX_UI_FONT_MEDIUM)); 	
	gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW MINI KINECT")); 	
	gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW CROPPED")); 	
	gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW DEPTH")); 	
	gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW CONTOUR")); 	
    
	
	
    
    ofAddListener(gui1->newGUIEvent,this,&kinect::guiEvent);
}

//--------------------------------------------------------------
void kinect::setGUI2()
{
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	
	gui2 = new ofxUICanvas(465+xInit, 0, length+xInit, ofGetHeight()); 
	gui2->addWidgetDown(new ofxUILabel("CROP", OFX_UI_FONT_MEDIUM)); 
    
	gui2->addWidgetDown(new ofxUI2DPad(length-xInit,120, ofPoint(0,640),  ofPoint(0,480), ofPoint(quadCropCorners[0].x, quadCropCorners[0].y), "TOP_RIGHT"));
	gui2->addWidgetDown(new ofxUI2DPad(length-xInit,120, ofPoint(0,640),  ofPoint(0,480), ofPoint(quadCropCorners[3].x, quadCropCorners[3].y), "BOTTOM_LEFT"));
    
    ofAddListener(gui2->newGUIEvent,this,&kinect::guiEvent);
}


//--------------------------------------------------------------
void kinect::guiEvent(ofxUIEventArgs &e)
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
	else if(name == "SHOW MINI KINECT")
	{
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        showRawKinect = toggle->getValue() == 1;        
	} 	
	else if(name == "SHOW CROPPED")
	{
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        showCropped = toggle->getValue() == 1;
        
	}
	else if(name == "SHOW DEPTH")
	{
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        debugKinect = toggle->getValue() == 1;
        
	}
	else if(name == "SHOW CONTOUR")
	{
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        showContour = toggle->getValue() == 1;
        
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

void kinect::save()
{
	gui1->saveSettings("GUI/settings.xml");
	gui2->saveSettings("GUI/crop.xml");
}

void kinect::exit() 
{
    kinect.close();
}








