#pragma once

#include "human.h"

class cup : public human
{
public:
    void setup(b2World * b2dworld, player (* playerList)[TOTAL_PLAYERS]);
    void update();
    void draw();
};

