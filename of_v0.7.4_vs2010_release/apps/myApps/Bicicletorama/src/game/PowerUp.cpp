
#include "PowerUp.h"

PowerUp::PowerUp(b2World * b2dworld)
{
	box.fixture.isSensor = true;

    box.setup(b2dworld, 0, 0, 100, 20);
	box.setData(new GenericData("powerup", this));

	box.setPosition(400,120);

	//box.fixture
}

void PowerUp::update() {
	//timer para se auto destruir
}

void PowerUp::draw() {
	box.draw();
}