#pragma once

#include "ofMain.h"
#include "config.h"

class arduino {

public:
    
    void setup();
    void update();
    ofSerial mySerial;
    string mySerialBuffer;
    
    float guidao[4];
    float velo[4];
    /*
    
public:

    void setup();
    void update();

    float guidao[4];
    float velo[4];
    
private:
    
    ofSerial mySerial;
    string mySerialBuffer;
    
    float lastReed[4];
    */
    
};
