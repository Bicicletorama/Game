#pragma once

#include "ofMain.h"


class Arduino : public ofSerial
{
    
public:
    
	void setup();
	void update();
    
	bool connected;
    
    
private:
    
    string buffer;

	int lastMillis;

	void onCompleteBuffer();
    

		
};

