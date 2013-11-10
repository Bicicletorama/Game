#include "cop.h"

void cop::setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS])
{
	spriteIdle.addFile("images/human/civil/idle/1.png");
	spriteIdle.addFile("images/human/civil/idle/2.png");

	spriteWalking.addFile("images/human/civil/walking/1.png");
	spriteWalking.addFile("images/human/civil/walking/2.png");
	spriteWalking.addFile("images/human/civil/walking/3.png");
	spriteWalking.addFile("images/human/civil/walking/4.png");
	spriteWalking.addFile("images/human/civil/walking/5.png");
	spriteWalking.addFile("images/human/civil/walking/3.png");

	spriteAttacking.addFile("images/human/civil/shooting/1.png");

	spriteDying.addFile("images/human/civil/dying/1.png");
	spriteDying.addFile("images/human/civil/dying/2.png");

	spriteIdle.setAnchorPercent(0.5, 0.5);
	spriteWalking.setAnchorPercent(0.5, 0.5);
	spriteAttacking.setAnchorPercent(0.5, 0.5);
	spriteDying.setAnchorPercent(0.5, 0.5);
	
	spriteIdle.play();
	spriteWalking.play();
	spriteAttacking.play();
	spriteDying.play();

	spriteDying.setLoop(false);
	
	spriteIdle.setFrameRate(2);
	spriteWalking.setFrameRate(6);
	spriteAttacking.setFrameRate(2);
	spriteDying.setFrameRate(2);
	
	human::setup(b2dworld, playerList);
	physics.setData(new GenericData("cop", this));
	type = COP;
}

void cop::update()
{
	human::think();

	switch (state) 
    {
		case IDLE:
			x = physics.getPosition().x;
			y = physics.getPosition().y;
			break;
        case WALKING:
        case LEAVING:
			updatePosition();
			updateRotation();
			physics.body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), rotation);
			break;	
		case ATTACKING:
			destX = (*playerList)[closestPlayer].x;
			destY = (*playerList)[closestPlayer].y;
			updateRotation();
			physics.body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), rotation);
			break;
        case DYING:
			break;
    }

	human::update();
}

void cop::draw()
{
	human::draw();
}

void cop::doSomething(){
	closestPlayer = findClosestPlayer(x, y);
	cout << closestPlayer << endl;
	if(closestPlayer==-1){
		//there is nobody close to you, go walk
		destX = ofRandom(WIDTH/2);
		destY = ofRandom(HEIGHT);
		changeState(WALKING);
		return;
	}

	int closestDistance = playerDistance(closestPlayer, x, y);

	//if target is near run away
	if(closestDistance<40000){//200*200=40000
		//find a place that there is no player close
		destX = ofRandom(WIDTH/2);
		destY = ofRandom(HEIGHT);
		int tries = 0;
		while(playerDistance(findClosestPlayer(destX, destY), destX, destY)<10000 && tries<10){
			destX = ofRandom(WIDTH/2);
			destY = ofRandom(HEIGHT);
			tries++;
		}
		changeState(WALKING);

	//if target is too far walk or idle
	}else if(closestDistance>160000){////400*400=160000
		if(state==WALKING){
			changeState(IDLE);
		}else{
			destX = (*playerList)[closestPlayer].x;
			destY = (*playerList)[closestPlayer].y;
			changeState(WALKING);
		}
		
	//if target is in a safe distance
	}else{
		if(state==ATTACKING) changeState(IDLE);
		else changeState(ATTACKING);
	}
}