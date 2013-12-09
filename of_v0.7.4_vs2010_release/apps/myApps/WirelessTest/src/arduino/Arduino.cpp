#include "arduino.h"


void Arduino::setup()
{
	listDevices();
	
    //connected = ofSerial::setup();
    connected = ofSerial::setup("COM8", 38400);
    buffer = "";

	lastMillis = 0;
}

void Arduino::update()
{
    int byte = readByte();
	//cout << byte << endl;
    while (byte != OF_SERIAL_NO_DATA && byte != OF_SERIAL_ERROR && byte != 0)
    {
        switch(byte)
        {
            case '\n':
            case '\r':
                if (buffer != "") 
				{
					onCompleteBuffer();
                    buffer = "";
                }
                break;
            default:
                buffer += (char)byte;
        }
        
        byte = readByte();
    }
}

void Arduino::onCompleteBuffer()
{
	int millis = ofGetElapsedTimeMillis()-lastMillis;

	lastMillis = ofGetElapsedTimeMillis();

	string value = ofToString(millis) + " - " + buffer + "\n";
	
	cout << value<< endl;

	ofBuffer buff = ofBufferFromFile("data.txt");
	buff.append(value);
	ofBufferToFile("data.txt", buff);

}

