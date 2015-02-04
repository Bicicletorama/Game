#include "arduino.h"


void Arduino::setup()
{
    ofSerial::setup();
    buffer = "";
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
                    if (data.size() >= 12)
                    {
                        impulse[0] += ofToInt(data[0]);
                        impulse[1] += ofToInt(data[1]);
                        impulse[2] += ofToInt(data[2]);
                        impulse[3] += ofToInt(data[3]);
                        
                        direction[0] = ofToFloat(data[4]);
                        direction[1] = ofToFloat(data[5]);
                        direction[2] = ofToFloat(data[6]);
                        direction[3] = ofToFloat(data[7]);
                        
                        clk[0] = ofToFloat(data[8]);
                        clk[1] = ofToFloat(data[9]);
                        clk[2] = ofToFloat(data[10]);
                        clk[3] = ofToFloat(data[11]);
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

float Arduino::getClk(int playerId)
{
    return clk[playerId];
}


