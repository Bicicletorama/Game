#include "bikeHub.h"

bikeHub::bikeHub()
{
	isConnected = false;
    buffer = "";
	
	for (int i = 0; i < TOTAL_PLAYERS; i++) {
		connections[i].isConnected = false;
		connections[i].wheel = false;
		connections[i].totalWheel = 0;
		connections[i].handlebar = 0;
	}
}

void bikeHub::setup()
{
	isConnected = serial.setup();
}

void bikeHub::update()
{
    int byte = serial.readByte();
    while (byte != OF_SERIAL_NO_DATA && byte != OF_SERIAL_ERROR && byte != 0)
    {
        switch(byte)
        {
            case '\n':
            case '\r':
                if (buffer != "") {
					onReceive();
                    buffer = "";
                }
                break;
            default:
                buffer += (char)byte;
        }
        
        byte = serial.readByte();
    }
}

void bikeHub::onReceive()
{
    vector<string> data = ofSplitString(buffer, " ");
	if (data.size() == 12) {
		parseConnection(0, ofToInt(data[0]), ofToInt(data[1]), ofToFloat(data[2]));
		parseConnection(1, ofToInt(data[3]), ofToInt(data[4]), ofToFloat(data[5]));
		parseConnection(2, ofToInt(data[6]), ofToInt(data[7]), ofToFloat(data[8]));
		parseConnection(3, ofToInt(data[9]), ofToInt(data[10]), ofToFloat(data[11]));
	}
}

void bikeHub::parseConnection(int id, bool connection, bool wheel, float handlebar)
{
	if (wheel == true && connections[id].wheel == false) {
		connections[id].totalWheel++;
	}

	connections[id].isConnected = connection;
	connections[id].wheel = wheel;
	connections[id].handlebar = handlebar;
}

bool bikeHub::isBikeConnected(int id)
{
	return (isConnected && connections[id].isConnected);
}

int bikeHub::getBikeImpulse(int id)
{
    int value = connections[id].totalWheel;
    connections[id].totalWheel = 0;
    return value;
}

float bikeHub::getBikeDirection(int id)
{
    return ofMap(connections[id].handlebar, 0, 1024, -1.0, 1.0);
}

bikeHub::~bikeHub()
{
	serial.close();
}