#include "Kinect.h"


void Kinect::setup(b2World * _world)
{
    world = _world;
    
	showKinect = false;
	
    BLUR_AMOUNT = 0;
    MIN_BLOB_AREA = 0;    
    TOLERANCE = 5;
    SENSIBILITY = 2;
    NEAR = 500;
    FAR = 4000;
    
	
	quadCropCorners.reserve(4);
	quadCropCorners.push_back( ofPoint(50,10 ));
	quadCropCorners.push_back( ofPoint(400,10) );
	quadCropCorners.push_back( ofPoint(400,300) );
	quadCropCorners.push_back( ofPoint(50, 300) );
	
    
    
	kinect.setRegistration(true);
    kinect.init(false, false, true);
	kinect.open(0);
    
    kinectNumPixels = kinect.width * kinect.height;
    
    backgroundPixels.allocate(kinect.width, kinect.height, 1);
    backgroundPixels.set(kinect.getFarClipping());
    
    lifePixels.allocate(kinect.width, kinect.height, 1);
    lifePixels.set(0);
    
	
    captureCount = 0;
    
	kinectImage.allocate(kinect.width, kinect.height);
    updateROI(0, 0, WIDTH, HEIGHT);
    
    scaledImage.allocate(WIDTH, HEIGHT);
    
    //first auto capture background
    captureBackground(true);
}

void Kinect::update()
{	
    kinect.update();
	
	if( kinect.isFrameNew() ) 
	{
        
        // capturing and saving background
        
        if (captureCount > 0)
        {
            captureBackground(false);
            captureCount--;
            return;
        }
        
        
        // capturing and saving kinect
        
        unsigned short * kinectRawDepthPixels = kinect.getRawDepthPixels();
        
        for (int i = 0; i < kinectNumPixels; i++)
        {
            if (kinectRawDepthPixels[i] > 1000
                && kinectRawDepthPixels[i] < backgroundPixels[i]-TOLERANCE
                && kinectRawDepthPixels[i] > NEAR
                && kinectRawDepthPixels[i] < FAR) {
                if (lifePixels[i] < SENSIBILITY) {
                    lifePixels[i]++;
                }
            } else {
                if (lifePixels[i] > 0) {
                    lifePixels[i]--;   
                }
            }
        }
        
        
        // gray image
        
        kinectImage.set(0);
        unsigned char * grayPixels = kinectImage.getPixels();
        
        for (int i = 0; i < kinectNumPixels; i++)
        {
            if (lifePixels[i] >= SENSIBILITY) {
                grayPixels[i] = 255;
            } else {
                grayPixels[i] = 0;
            }
        }
		kinectImage.flagImageChanged();
        
        
        // blur
        
		kinectImage.blur(BLUR_AMOUNT);
        kinectImage.threshold(30);
        
        
        // find contours
        
        scaledImage.scaleIntoMe(kinectImage);
		contourFinder.findContours(scaledImage, MIN_BLOB_AREA, 2000000, 100, false);
        
        
		// triangulate
        
		triangle.clear();
        for (int i = 0; i < contourFinder.blobs.size(); i++) {
			triangle.triangulate( contourFinder.blobs[i].pts, max( 3.0f, (float)contourFinder.blobs[i].pts.size()/12) );
        }
		
		for ( int i = polys.size()-1; i >= 0; i--) {
            polys[i].destroy();
        }
		
		polys.clear();
		
		ofxTriangleData * tData;
		
		for (int i = triangle.triangles.size()-1; i >= 0; i--) 
		{
			tData = &triangle.triangles[i];
			
			ofxBox2dPolygon poly;
			poly.addVertex(tData->a.x, tData->a.y);
			poly.addVertex(tData->b.x, tData->b.y);
			poly.addVertex(tData->c.x, tData->c.y);
			poly.create(world);
			polys.push_back(poly);
		}
        
	}	
    
}

void Kinect::draw()
{
    ofSetColor(255, 255, 255);
    
    if (showCropped) {
        kinectImage.drawROI(0,0, WIDTH, HEIGHT);
    }
	if (showContour) {
        ofSetColor(255, 0, 0);
        for (int i = 0; i < contourFinder.blobs.size(); i++) {
            ofBeginShape();
            for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++){
                ofVertex(contourFinder.blobs[i].pts[j].x, contourFinder.blobs[i].pts[j].y);
            }
            ofEndShape(true);
        }
        ofSetColor(255);
    }
	if (showKinect) {
        kinect.drawDepth(400, 500, 200, 150);
        kinectImage.draw(610, 500, 200, 150);
        contourFinder.draw(610, 500, 200, 150);
    }
}

void Kinect::keyPressed(int key)
{   
	switch (key) 
	{
		case 'k':
			captureBackground(true);
			break;
	}
}

void Kinect::updateROI(int x, int y, int w, int h)
{
    kinectImage.setROI(x, y, w, h);
}

void Kinect::captureBackground(bool clearBackground = false)
{
    if (clearBackground) {
        captureCount = 60;
        backgroundPixels.set(kinect.getFarClipping());
    }
    
    unsigned short * pixels = kinect.getRawDepthPixels();
    for (int i = 0; i < kinectNumPixels; i++)
    {
        if (pixels[i] == 0) {
            pixels[i] = kinect.getFarClipping();
        }
        backgroundPixels[i] = min(backgroundPixels[i], pixels[i]);
    }
}

void Kinect::exit()
{
    kinect.close();
}








