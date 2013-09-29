#pragma once

#include "ofMain.h"
#include "config.h"

class arduino {

public:
    
    
    float POTENCIOMETRO_MIDDLE;
    float POTENCIOMETRO_RANGE;
    
    void setup();
    void update();
    void exit();
    
    void setupArduino(const int & version);
    
    ofArduino m_arduino;
    
    float analog[TOTAL_PLAYERS];
    float digital[TOTAL_PLAYERS];
    
    float guidao[TOTAL_PLAYERS];
    float velo[TOTAL_PLAYERS];
    
    
    float lastVelo[TOTAL_PLAYERS];
    
    
};
