#include "PowerChange.h"

PowerChange::PowerChange()
{
	enabled = false;
	millis = 0;
	body = NULL;
}

void PowerChange::setup(b2World * world, float isPowerUp)
{
	if (isPowerUp) {
		//power up
		value = 3.f;

		image.loadImage("images/ciclovia.png");

		body = new ofxBox2dRect();
		body->fixture.isSensor = true;
		((ofxBox2dRect*)body)->setup(world, 0, 0, 50, 20);
	} 
	else {
		//power down
		value = 1/4.f;

		image.loadImage("images/buraco.png");
		
		body = new ofxBox2dRect();
		body = new ofxBox2dCircle();
		body->fixture.isSensor = true;
		((ofxBox2dCircle*)body)->setup(world, 0, 0, 30);
	}

	body->setData(new GenericData("powerChange", &value));
}

void PowerChange::update() 
{
	if (enabled && ofGetElapsedTimeMillis() - millis > POWER_CHANGE_LIFE_TIME) {
		body->setPosition(-9999,-9999); //leave it outside the window to remove //TODO trabalhar com b2Body->SetAwake()
		enabled = false;
	}
}

void PowerChange::draw() 
{
	if (enabled) {
		//body->draw();
		
		ofPushMatrix();
		ofTranslate(body->getPosition());
		ofRotate(body->getRotation());
			image.draw(-image.width/2.f, -image.height/2.f);
		ofPopMatrix();
	}
}

void PowerChange::showAt(float x, float y) 
{
	body->body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), ofRandom(HALF_PI));
	millis = ofGetElapsedTimeMillis();
	enabled = true;
}

PowerChange::~PowerChange() 
{
	if (body != NULL) {
		delete body;
	}
}