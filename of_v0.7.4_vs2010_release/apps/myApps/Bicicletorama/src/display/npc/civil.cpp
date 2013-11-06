#include "civil.h"

void civil::setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS])
{
	spriteIdle.addFile("images/human/mafestante/careca/idle/1.png");
	spriteIdle.addFile("images/human/mafestante/careca/idle/2.png");

	spriteWalking.addFile("images/human/mafestante/careca/walking/1.png");
	spriteWalking.addFile("images/human/mafestante/careca/walking/2.png");
	spriteWalking.addFile("images/human/mafestante/careca/walking/3.png");
	spriteWalking.addFile("images/human/mafestante/careca/walking/4.png");
	spriteWalking.addFile("images/human/mafestante/careca/walking/5.png");
	spriteWalking.addFile("images/human/mafestante/careca/walking/3.png");

	spriteAttacking.addFile("images/human/civil/shooting/1.png");

	spriteDying.addFile("images/human/mafestante/careca/dying/1.png");
	spriteDying.addFile("images/human/mafestante/careca/dying/2.png");

	spriteIdle.setAnchorPercent(0.5, 0.5);
	spriteWalking.setAnchorPercent(0.5, 0.5);
	spriteAttacking.setAnchorPercent(0.5, 0.5);
	spriteDying.setAnchorPercent(0.5, 0.5);
	
	spriteIdle.play();
	spriteWalking.play();
	spriteAttacking.play();
	spriteDying.play();
	
	spriteIdle.setFrameRate(2);
	spriteWalking.setFrameRate(6);
	spriteAttacking.setFrameRate(2);
	spriteDying.setFrameRate(2);

	human::setup(b2dworld, playerList);
	physics.setData(new GenericData("civil", this));
}

void civil::update()
{
	human::update();
}

void civil::draw()
{
	human::draw();
}