#include "civil.h"

void civil::setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS])
{
	const char* spritesNames[] = {"blackblock", "careca", "sem_camisa", "galego", "menina"};
	int roundIndex = floor(ofRandom(5));
	string spriteName = spritesNames[roundIndex];

	spriteIdle.addFile("images/human/manifestante/" + spriteName + "/idle/1.png");
	spriteIdle.addFile("images/human/manifestante/" + spriteName + "/idle/2.png");

	spriteWalking.addFile("images/human/manifestante/" + spriteName + "/walking/1.png");
	spriteWalking.addFile("images/human/manifestante/" + spriteName + "/walking/2.png");
	spriteWalking.addFile("images/human/manifestante/" + spriteName + "/walking/3.png");
	spriteWalking.addFile("images/human/manifestante/" + spriteName + "/walking/4.png");
	spriteWalking.addFile("images/human/manifestante/" + spriteName + "/walking/5.png");
	spriteWalking.addFile("images/human/manifestante/" + spriteName + "/walking/3.png");
	
	spriteAttacking.addFile("images/human/manifestante/" + spriteName + "/cartaz/1.png");
	spriteAttacking.addFile("images/human/manifestante/" + spriteName + "/cartaz/2.png");
	spriteAttacking.addFile("images/human/manifestante/" + spriteName + "/cartaz/3.png");
	spriteAttacking.addFile("images/human/manifestante/" + spriteName + "/cartaz/4.png");
	spriteAttacking.addFile("images/human/manifestante/" + spriteName + "/cartaz/5.png");

	spriteDying.addFile("images/human/manifestante/" + spriteName + "/dying/1.png");
	spriteDying.addFile("images/human/manifestante/" + spriteName + "/dying/2.png");

	spriteRising.addFile("images/human/manifestante/" + spriteName + "/dying/1.png");

	spriteLeaving.addFile("images/human/manifestante/" + spriteName + "/walking/1.png");
	spriteLeaving.addFile("images/human/manifestante/" + spriteName + "/walking/2.png");
	spriteLeaving.addFile("images/human/manifestante/" + spriteName + "/walking/3.png");
	spriteLeaving.addFile("images/human/manifestante/" + spriteName + "/walking/4.png");
	spriteLeaving.addFile("images/human/manifestante/" + spriteName + "/walking/5.png");
	spriteLeaving.addFile("images/human/manifestante/" + spriteName + "/walking/3.png");
	
	spriteIdle.setAnchorPercent(0.5, 0.5);
	spriteWalking.setAnchorPercent(0.5, 0.5);
	spriteAttacking.setAnchorPercent(0.5, 0.5);
	spriteDying.setAnchorPercent(0.5, 0.5);
	spriteRising.setAnchorPercent(0.5, 0.5);
	spriteLeaving.setAnchorPercent(0.5, 0.5);
	
	spriteIdle.play();
	spriteWalking.play();
	spriteAttacking.play();
	spriteDying.play();
	spriteRising.play();
	spriteLeaving.play();

	spriteDying.setLoop(false);
	
	spriteIdle.setFrameRate(2);
	spriteWalking.setFrameRate(6);
	spriteAttacking.setFrameRate(6);
	spriteDying.setFrameRate(2);
	spriteLeaving.setFrameRate(6);
	
	poster.loadImage("images/cartazes/" + ofToString(floor(ofRandom(3))+1) + ".png");

	human::setup(b2dworld, playerList);
	physics.setData(new GenericData("civil", this));
	type = CIVIL;
}

void civil::update()
{
	human::think();

	switch (state) 
    {
		case IDLE:
		case RISING:
        case DYING:
			x = physics.getPosition().x;
			y = physics.getPosition().y;
			break;
        case WALKING:
        case LEAVING:
		case ATTACKING:
			updatePosition();
			updateRotation();
			physics.body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), rotation);
			break;
    }

	human::update();
}

void civil::draw()
{
	human::draw();

	if(state==ATTACKING) {
		
		ofPushMatrix();
		ofTranslate(sprite->x, sprite->y);
		ofRotate(sprite->rotation);
		poster.draw(-sprite->getAnchorPoint().x, -sprite->getAnchorPoint().y);
		ofPopMatrix();
	}
}

void civil::doSomething(){
	closestPlayer = findClosestPlayer(x, y);
	if(closestPlayer==-1){
		//there is nobody close to you, go walk
		destX = WIDTH/2 + ofRandom(WIDTH/2);
		destY = ofRandom(HEIGHT);
		changeState(WALKING);
		return;
	}

	int closestDistance = playerDistance(closestPlayer, x, y);

	//if target is near run away
	if(closestDistance<40000){//200*200=40000
		//find a place that there is no player close
		destX = WIDTH/2 + ofRandom(WIDTH/2);
		destY = ofRandom(HEIGHT);
		int tries = 0;
		while(playerDistance(findClosestPlayer(destX, destY), destX, destY)<10000 && tries<10){
			destX = WIDTH/2 + ofRandom(WIDTH/2);
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