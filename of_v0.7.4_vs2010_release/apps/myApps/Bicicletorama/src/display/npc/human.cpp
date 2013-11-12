
#include "human.h"


human::~human(){
	physics.body->GetWorld()->DestroyBody( physics.body );
}

void human::setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS])
{
	this->playerList = playerList;

	width = 24;
	height = 30;

	closestPlayer = -1;

	MIN_CHANGE_TIME = 5000;

	completed = false;
    
	//sprites
	sprite = &spriteIdle;
    
	//box2d
	physics.setPhysics(3.0, 0.53, 0.1);
	physics.setup(b2dworld, 0, 0, width, height);
	
	
	x = 0;
	y = 0;
	
	distX = 0;
	distY = 0;
 
	rotation = 0;

	startAtRandomPosition();
}

void human::startAtRandomPosition() 
{
	int margin = 10;
	float whereToGo = ofRandom(1.0);
	//TOP
	if(whereToGo>0.75)		physics.body->SetTransform(b2Vec2(b2dNum(ofRandom(WIDTH)), b2dNum(-margin)), 0);
	//RIGHT
	else if(whereToGo>0.5)	physics.body->SetTransform(b2Vec2(b2dNum(WIDTH+margin), b2dNum(ofRandom(HEIGHT))), 0);
	//BOTTOM
	else if(whereToGo>0.25)	physics.body->SetTransform(b2Vec2(b2dNum(ofRandom(WIDTH)), b2dNum(HEIGHT+margin)), 0);
	//LEFT
	else					physics.body->SetTransform(b2Vec2(b2dNum(-margin), b2dNum(ofRandom(HEIGHT))), 0);
	
    changeState(IDLE);
}

void human::die() 
{
	if(state==LEAVING) return;
    changeState(DYING);
}

void human::leave() 
{
	if(state==LEAVING) return;

	int margin = 50;
	float whereToGo = ofRandom(1.0);
	if(whereToGo>0.75) {
		//TOP
		destX = ofRandom(WIDTH);
		destY = -margin;
	} else if(whereToGo>0.5) {
		//RIGHT
		destX = WIDTH+margin;
		destY = ofRandom(HEIGHT);
	} else if(whereToGo>0.25) {
		//BOTTOM
		destX = ofRandom(WIDTH);
		destY = HEIGHT+margin;
	} else {
		//LEFT
		destX = -margin;
		destY = ofRandom(HEIGHT);
	}
	
    changeState(LEAVING);
}

void human::update()
{
    sprite->update();
    sprite->setRotation(physics.getRotation());
    sprite->setPosition(physics.getPosition());
}

void human::draw() 
{
	sprite->draw();
}


void human::changeState(states _state){
	state = _state;

	switch (state)
    {
		case IDLE:
			MIN_CHANGE_TIME = 3000;
			sprite = &spriteIdle;
            break;	
        case WALKING:
			MIN_CHANGE_TIME = 5000;
			sprite = &spriteWalking;
            break;	
        case LEAVING:
			MIN_CHANGE_TIME = 15000;
			sprite = &spriteLeaving;
            break;	
        case ATTACKING:
			MIN_CHANGE_TIME = 1000;
			sprite = &spriteAttacking;
			attack a;
				a.startX = x;
				a.startY = y;
				a.endX = (*playerList)[closestPlayer].x;
				a.endY = (*playerList)[closestPlayer].y;
			ofNotifyEvent(onAttack, a);
            break;	
        case DYING:
			sprite = &spriteDying;
            break;
    }

	lastTimeIChanged = ofGetElapsedTimeMillis();
}

bool human::hasComplete()
{
	return completed;
}

int human::getState()
{
	return state;
}

void human::think(){

	if(ofGetElapsedTimeMillis() - lastTimeIChanged > MIN_CHANGE_TIME){
		if(state==DYING){
			leave();
		}else if(state==LEAVING){
			completed = true;
			return;
		}

		float shouldIChange = ofRandom(1.0);
		if(shouldIChange<0.9) return;

		doSomething();
	}
}

void human::doSomething(){
	//override it
}

int human::findClosestPlayer(int _x, int _y){
	int foundIndex = -1;
	int dist=1000000;
	for(int i=0; i<TOTAL_PLAYERS; i++){
		if((*playerList)[i].isActive()) {
			int tempDist = playerDistance(i, _x, _y);
			if(tempDist<dist && tempDist>0){
				foundIndex = i;
				dist = tempDist;
			}
		}
	}

	return foundIndex;
}

int human::playerDistance(int playerIndex, int _x, int _y){
	return ofDistSquared((*playerList)[playerIndex].x, (*playerList)[playerIndex].y, _x, _y);
}

void human::updatePosition(){
	//deaccel
	float slowDistX = distX/15;
	float slowDistY = distY/15;

	// update position
	x += slowDistX > 3 ? -3 : slowDistX < -3 ? 3 : -slowDistX;
	y += slowDistY > 3 ? -3 : slowDistY < -3 ? 3 : -slowDistY;
}

void human::updateRotation(){
	distX = x - destX;
	distY = y - destY;
	rotation = getRadians(distX, distY);
}

float human::getRadians(float delta_x, float delta_y){
	float r = PI-atan2(delta_y, delta_x)*-1;
 
	if (delta_y < 0)
	{
		r += TWO_PI;
	}
	return r;
}