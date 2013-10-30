#include "cup.h"

void cup::setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS])
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
	
	spriteIdle.setFrameRate(2);
	spriteWalking.setFrameRate(6);
	spriteAttacking.setFrameRate(2);
	spriteDying.setFrameRate(2);

	human::setup(b2dworld, playerList);
}

void cup::update()
{
	human::update();
}

void cup::draw()
{
	human::draw();
}