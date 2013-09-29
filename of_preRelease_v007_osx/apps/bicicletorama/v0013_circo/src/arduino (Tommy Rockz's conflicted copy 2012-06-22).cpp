#include "arduino.h"


static const int SERIAL_ID = 5;
static const int SERIAL_BAUND = 9600;

static const int POTENCIOMETRO_MIDDLE = 490;
static const int POTENCIOMETRO_RANGE = 300;


void arduino::setup()
{
    if (USE_ARDUINO)
    {
        mySerialBuffer = "";
        mySerial.enumerateDevices();
        
        //if( mySerial.setup( SERIAL_ID , SERIAL_BAUND ) ) {
		if( mySerial.setup( 5 , 9600 ) ) {
            cout << "arduino ok" << endl;
        } else {
            cout << "arduino error" << endl;
        }
    }
}

void arduino::update()
{   
	
	cout << "ARDUINO - update: "  << endl;
	
    if (USE_ARDUINO)
    {
		
		cout << "ARDUINO - primeira checagem: "  << endl;
		
		int millis;
		cout << "ARDUINO 2"  << endl;
		
        // clear all current velo
        for (int i = 0; i < TOTAL_PLAYERS; i++) {
					cout << "ARDUINO 3"  << endl;
            velo[i] = 0;
        }
		cout << "ARDUINO 4" << endl;
		cout << "ARDUINO 4.5" << mySerial.available()  << endl;
        while (mySerial.available())
        {
					cout << "ARDUINO 5"  << endl;
			cout << "ARDUINO - mybyte: ";
            char myByte = mySerial.readByte();
			
			cout << myByte  << endl;
			
			
            // carriage: do nothing
            if( (int)myByte == 13 ) {
                // return: new line, time to process last line
            }
            else if( (int)myByte == 10 ) 
            {
                stringstream tempstream;
                stringstream stream;
                string s;
                int paramCount = 0;
                
                // pass string to streams
                tempstream << mySerialBuffer;
                stream << mySerialBuffer;
                
                // use tempstream to count number of params
                while (tempstream >> s) {
                    paramCount++;
                }
				
				cout << "ARDUINO - PARAM: " << paramCount  << endl;
                
                // we expect 8 params: 123 123 123 123 0 0 1 1
                // if we dont have it, wait next update
                if( paramCount == 9 )
                {
                    // temp storage for current reed values
                    float reed[4];
                    
                    //use stream to feed the variables
                    stream >> guidao[0] >> guidao[1] >> guidao[2] >> guidao[3] >> reed[0] >> reed[1] >> reed[2] >> reed[3] >> millis;
                    
                            cout << "ARDUINO: " << guidao[0] << " - " << reed[0] << "  - MILLIS: "<< millis  << endl;
                    // for each player
                    for (int i = 0; i < TOTAL_PLAYERS; i++)
                    {
                        //convert pontenciometro values
                        guidao[i] = ofMap(guidao[i], POTENCIOMETRO_MIDDLE-POTENCIOMETRO_RANGE, POTENCIOMETRO_MIDDLE+POTENCIOMETRO_RANGE, -1, 1);
                        
                        // check if the reed enter on HIGH mode
                        if (lastReed[i] == 0 && reed[i] == 1) {
                            // if true, plus 1 to total impulses at this update
                            velo[i]++;
                        }
                        lastReed[i] = reed[i];
                    }
                    
                    // clear string for next line
                    mySerialBuffer = "";
                }
            } 
            else {
                // add byte to string
                mySerialBuffer += myByte;
            }
        }
        
//        cout << "ARDUINO: " << guidao[0] << " - " << velo[0] << "  - MILLIS: "<< millis  << endl;
        
    }
}

