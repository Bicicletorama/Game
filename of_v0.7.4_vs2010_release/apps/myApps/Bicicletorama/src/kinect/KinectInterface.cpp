#include "KinectInterface.h"


void KinectInterface::setup(b2World * _world)
{
    world = _world;
    
	showKinect = false;
	
    BLUR_AMOUNT = 0;
    MIN_BLOB_AREA = 0;    
    TOLERANCE = 5;
    SENSIBILITY = 2;

	HARDCODE_NEAR = 2000;
	FAR_BOTTOM = 4000;
	FAR_TOP = 4000;
    
	
	quadCropCorners.reserve(4);
	quadCropCorners.push_back( ofPoint(50,10 ));
	quadCropCorners.push_back( ofPoint(400,10) );
	quadCropCorners.push_back( ofPoint(400,300) );
	quadCropCorners.push_back( ofPoint(50, 300) );

	//Kinect
	ofxKinectNui::InitSetting initSetting;
	initSetting.grabVideo = false;
	initSetting.grabDepth = true;
	initSetting.grabAudio = false;
	initSetting.grabLabel = false;
	initSetting.grabSkeleton = false;
	initSetting.grabCalibratedVideo = false;
	initSetting.grabLabelCv = false;
	initSetting.depthResolution = NUI_IMAGE_RESOLUTION_640x480;
	kinect.init(initSetting);
	kinect.open();
	
	kinectNumPixels = KINECT_WIDTH * KINECT_HEIGHT;
    
    backgroundPixels.allocate(KINECT_WIDTH, KINECT_HEIGHT, 1);
	backgroundPixels.set(kinect.getFarClippingDistance());
    
    lifePixels.allocate(KINECT_WIDTH, KINECT_HEIGHT, 1);
    lifePixels.set(0);
    
	
    captureCount = 0;
    
	depthImage.allocate(KINECT_WIDTH, KINECT_HEIGHT);
	pbImage.allocate(KINECT_WIDTH, KINECT_HEIGHT);
	thresholdedImage.allocate(KINECT_WIDTH, KINECT_HEIGHT);
    updateROI(0, 0, WIDTH, HEIGHT);
    
    scaledImage.allocate(WIDTH, HEIGHT);
	
    //first auto capture background
    captureBackground(true);
}

void KinectInterface::update()
{	
    kinect.update();
	
	if( kinect.isOpened() ) 
	{
        depthImage.setFromPixels(kinect.getDepthPixels());
        
        // capturing and saving background
        
        if (captureCount > 0)
        {
            captureBackground(false);
            captureCount--;
            return;
        }
        
        
        // capturing and saving kinect
        
		ofShortPixels kinectRawDepthPixels = kinect.getDistancePixels();
        
        for (int i = 0; i < kinectNumPixels; i++)
        {
            if (kinectRawDepthPixels[i] > HARDCODE_NEAR && kinectRawDepthPixels[i] < backgroundPixels[i]-TOLERANCE) {
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

		pbImage.set(0);
        unsigned char * pbPixels = pbImage.getPixels();
        for (int i = 0; i < kinectNumPixels; i++)
        {
            if (lifePixels[i] >= SENSIBILITY) {
                pbPixels[i] = 255;
            } else {
                pbPixels[i] = 0;
            }
        }
		pbImage.flagImageChanged();
        
        
		thresholdedImage.setFromPixels(pbImage.getRoiPixels(), pbImage.getROI().width, pbImage.getROI().height);
        thresholdedImage.blur(BLUR_AMOUNT);
        thresholdedImage.threshold(30);
		thresholdedImage.mirror(true, false); //flip hardcode image
        
        
        // find contours
        scaledImage.scaleIntoMe(thresholdedImage);
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

void KinectInterface::draw()
{
    ofSetColor(255, 255, 255);
    
    if (showCropped) {
        depthImage.drawROI(0,0, WIDTH, HEIGHT);
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
		depthImage.draw(190, 500, 200, 150);
		pbImage.draw(400, 500, 200, 150);
        thresholdedImage.draw(610, 500, 200, 150);
        contourFinder.draw(610, 500, 200, 150);
    }
}

void KinectInterface::keyPressed(int key)
{   
	switch (key) 
	{
		case 'k':
			captureBackground(true);
			break;
	}
}

void KinectInterface::updateROI(int x, int y, int w, int h)
{
    depthImage.setROI(x, y, w, h);
	pbImage.setROI(x, y, w, h);
}

void KinectInterface::setAngle(int _angle)
{
	angle = _angle;
	if(angle < -27) angle = -27;
	if(angle > 27) angle = 27;
	kinect.setAngle(angle);
}

void KinectInterface::captureBackground(bool clearBackground = false)
{
	if(!kinect.isOpened()) return;

    if (clearBackground) {
        captureCount = 60;
		backgroundPixels.set(kinect.getFarClippingDistance());

		//a base do background é a interpolação, depois ele faz o mapeamento em cima
		for (int i = 0; i < KINECT_HEIGHT; i++)
		{
			float valueY = ofMap(i, 0, KINECT_HEIGHT-1, FAR_TOP, FAR_BOTTOM);
			for (int j = 0; j < KINECT_WIDTH; j++) {
				backgroundPixels[ (i*KINECT_WIDTH) + j ] = valueY;
			}
		}
    }
	
    ofShortPixels pixels = kinect.getDistancePixels();
    for (int i = 0; i < kinectNumPixels; i++)
    {
        if (pixels[i] > HARDCODE_NEAR) {
			backgroundPixels[i] = min(backgroundPixels[i], pixels[i]);
        }
    }
}

void KinectInterface::exit()
{
    kinect.close();
}








