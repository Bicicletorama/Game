#pragma once

#include "human.h"

class cop : public human
{
public:
    void setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS]);
    void update();
    void draw();
};
