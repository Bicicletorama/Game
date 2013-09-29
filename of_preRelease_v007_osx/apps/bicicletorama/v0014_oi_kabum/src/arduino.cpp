#include "arduino.h"




void arduino::setup()
{
    
    POTENCIOMETRO_MIDDLE = 490;
    POTENCIOMETRO_RANGE = 300;
    
    //m_arduino.connect("/pdev/tty.usbmodemfd121", 57600);
    m_arduino.connect("/dev/tty.usbmodemfa1341", 57600);
    m_arduino.setDigitalHistoryLength(10);
	ofAddListener(m_arduino.EInitialized, this, &arduino::setupArduino);
    
    //mapeamento das portas do arduino
    
    analog[0] = 0;
    analog[1] = 2;
    analog[2] = 4;
    //analog[3] = 5;
    
    digital[0] = 2;
    digital[1] = 11                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ;
    digital[2] = 12;
    //digital[3] = 13;
        
}

void arduino::setupArduino(const int & version) 
{
    // remove listener because we don't need it anymore
    ofRemoveListener(m_arduino.EInitialized, this, &arduino::setupArduino);
    
    // this is where you setup all the pins and pin modes, etc
    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        m_arduino.sendDigitalPinMode( digital[i], ARD_INPUT);
        m_arduino.sendAnalogPinReporting( analog[i], ARD_ANALOG);
    }
}

void arduino::update()
{
    m_arduino.update();
    
    for(int i=0; i<TOTAL_PLAYERS;i++)
    {
        cout << i << ": " << m_arduino.getAnalog(analog[i]) << " " << m_arduino.getDigital(digital[i]) << " || " ;
        
        guidao[i] = ofMap(m_arduino.getAnalog( analog[i] ), POTENCIOMETRO_MIDDLE-POTENCIOMETRO_RANGE, POTENCIOMETRO_MIDDLE+POTENCIOMETRO_RANGE,-1,1);
        
        velo[i] = 0;
        
        list<int>* lista = m_arduino.getDigitalHistory(digital[i]);
        for (list<int>::iterator it = lista->begin(); it != lista->end(); it++) {
            if (lastVelo[i] == 0 && *it == 1) {
                velo[i] = 1;
            }
            //cout << *it << " ";
        }
        //cout << endl;
        lastVelo[i] = velo[i];
        lista->clear();
        
        /*int reed = m_arduino.getDigital( digital[i] );
        if (lastVelo[i] == 0 && reed == 1) {
            velo[i] = 1;
        } else {
            velo[i] = 0;
        }
        lastVelo[i] = reed;*/
    
        //cout << i << ": " << guidao[i] << " " << velo[i] << " || " ;
        
    }
    cout << endl;
    

}

void arduino::exit()
{
    m_arduino.disconnect();
}



