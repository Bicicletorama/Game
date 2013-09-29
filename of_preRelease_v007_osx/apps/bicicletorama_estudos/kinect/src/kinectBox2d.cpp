#include "kinectBox2d.h"

void kinectBox2d::setup() 
{
	ofSetFrameRate( 60 );
	
	kinect.setRegistration( true );
    kinect.init();
	kinect.open( 0 );
	
	colorImg.allocate( kinect.width, kinect.height );
	grayImage.allocate( kinect.width, kinect.height );
	grayThreshNear.allocate( kinect.width, kinect.height );
	grayThreshFar.allocate( kinect.width, kinect.height );
	
	nearThreshold = 255;
	farThreshold = 200;
	
	physics.init();
	physics.createBounds();
	physics.setGravity(0, 10);
	physics.checkBounds(true);
}

void kinectBox2d::update() 
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
		
		contourFinder.findContours( grayImage, 20, (kinect.getWidth()*kinect.getHeight())/3, 5, false );
		
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
			poly.create(physics.getWorld());
			polys.push_back(poly);
		}
		
		physics.update();
	}	
}

void kinectBox2d::draw()
{
	
	ofSetColor(255, 255, 255);
	
	grayImage.draw(0, 0, kinect.getWidth(), kinect.getHeight());
	
	nbCircles = circles.size();
	for(int i=0; i<nbCircles; i++) circles[i].draw();
	
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
}

void kinectBox2d::keyPressed ( int key ) 
{
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
		case 'c':
			ofxBox2dCircle circle;
			circle.setPhysics(0.5, 0.53,10.1);
			circle.setup(physics.getWorld(), mouseX, mouseY, 20);
			circles.push_back(circle);
			break;
	}
}

void kinectBox2d::exit() { kinect.close();}
