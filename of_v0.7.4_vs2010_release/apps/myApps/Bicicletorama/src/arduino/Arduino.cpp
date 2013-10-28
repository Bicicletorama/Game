#include "arduino.h"


void Arduino::setup()
{
    connected = ofSerial::setup();
    buffer = "";
	
	for (int i = 0; i < TOTAL_PLAYERS; i++) {
		impulse[i] = 0;
		direction[i] = 0;
	}
}

void Arduino::update()
{
    int byte = readByte();
    while (byte != OF_SERIAL_NO_DATA && byte != OF_SERIAL_ERROR)
    {
        switch(byte)
        {
            case '\n':
            case '\r':
                if (buffer != "")
                {
                    vector<string> data = ofSplitString(buffer, " ");
                    if (data.size() >= 8)
                    {
                        impulse[0] += ofToInt(data[0]);
                        impulse[1] += ofToInt(data[1]);
                        impulse[2] += ofToInt(data[2]);
                        impulse[3] += ofToInt(data[3]);
                        
                        direction[0] = ofToFloat(data[4]);
                        direction[1] = ofToFloat(data[5]);
                        direction[2] = ofToFloat(data[6]);
                        direction[3] = ofToFloat(data[7]);
                    }
                    buffer = "";
                }
                break;
            default:
                buffer += (char)byte;
        }
        
        byte = readByte();
    }
}

int Arduino::getImpulse(int playerID)
{
    int r = impulse[playerID];
    impulse[playerID] = 0;
    return r;
}

float Arduino::getDirection(int playerID)
{
    return direction[playerID];
}



