#include "KinectInterface.h"


void KinectInterface::setup(b2World * _world)
{
    world = _world;
    
	showKinect = false;
	
    BLUR_AMOUNT = 0;
    MIN_BLOB_AREA = 0;    
    TOLERANCE = 5;
    SENSIBILITY = 2;
    
	
	quadCropCorners.reserve(4);
	quadCropCorners.push_back( ofPoint(50,10 ));
	quadCropCorners.push_back( ofPoint(400,10) );
	quadCropCorners.push_back( ofPoint(400,300) );
	quadCropCorners.push_back( ofPoint(50, 300) );

	//Kinect
	ofxKinectNui::InitSetting initSetting;
	initSetting.grabVideo = false;
	initSetting.grabDepth = false;
	initSetting.grabAudio = false;
	initSetting.grabLabel = false;
	initSetting.grabSkeleton = true;
	initSetting.grabCalibratedVideo = false;
	initSetting.grabLabelCv = false;
	initSetting.videoResolution = NUI_IMAGE_RESOLUTION_320x240;
	initSetting.depthResolution = NUI_IMAGE_RESOLUTION_320x240;
	m_kinect.init(initSetting);
	m_kinect.open();
	m_kinect.addKinectListener(this, &KinectInterface::kinectPlugged, &KinectInterface::kinectUnplugged);
	
	bPlugged = m_kinect.isConnected();



    
    kinectNumPixels = KINECT_WIDTH * KINECT_HEIGHT;
    
    backgroundPixels.allocate(KINECT_WIDTH, KINECT_HEIGHT, 1);
	backgroundPixels.set(m_kinect.getFarClippingDistance());
    
    lifePixels.allocate(KINECT_WIDTH, KINECT_HEIGHT, 1);
    lifePixels.set(0);
    
	
    captureCount = 0;
    
	kinectImage.allocate(KINECT_WIDTH, KINECT_HEIGHT);
    updateROI(0, 0, WIDTH, HEIGHT);
    
    scaledImage.allocate(WIDTH, HEIGHT);
    
    //first auto capture background
    captureBackground(true);
}

void KinectInterface::update()
{	
    m_kinect.update();
	
	if( m_kinect.isFrameNew() ) 
	{
        
        // capturing and saving background
        
        if (captureCount > 0)
        {
            captureBackground(false);
            captureCount--;
            return;
        }
        
        
        // capturing and saving kinect
        
		ofPixels kinectRawDepthPixels = m_kinect.getDepthPixels();
        
        for (int i = 0; i < kinectNumPixels; i++)
        {
            if (kinectRawDepthPixels[i] > 0 && kinectRawDepthPixels[i] < backgroundPixels[i]-TOLERANCE) {
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

void KinectInterface::draw()
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
        m_kinect.drawDepth(400, 500, 200, 150);
        kinectImage.draw(610, 500, 200, 150);
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
    kinectImage.setROI(x, y, w, h);
}

void KinectInterface::captureBackground(bool clearBackground = false)
{
    if (clearBackground) {
        captureCount = 60;
		backgroundPixels.set(kinect.getFarClippingDistance());
    }

	if(!bPlugged) return;

							//getRawDepthPixels
    ofPixels pixels = m_kinect.getDepthPixels();
    for (int i = 0; i < kinectNumPixels; i++)
    {
        if (pixels[i] == 0) {
								//getFarClipping
            pixels[i] = m_kinect.getFarClippingDistance();
        }
        backgroundPixels[i] = min(backgroundPixels[i], pixels[i]);
    }
}

//--------------------------------------------------------------
void KinectInterface::kinectPlugged(){
	bPlugged = true;
}

//--------------------------------------------------------------
void KinectInterface::kinectUnplugged(){
	bPlugged = false;
}

void KinectInterface::exit()
{
    m_kinect.close();
}








