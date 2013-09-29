#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    mySerialBuffer = "";
    mySerial.enumerateDevices();
    
    if( mySerial.setup( 5 , 9600 ) ) {
        cout << "arduino ok" << endl;
    } else {
        cout << "arduino error" << endl;
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if(mySerial.available()){
        
        char myByte = mySerial.readByte();
        
        // carriage: do nothing
        
        if( (int)myByte == 13 ){
            
        
        // return: new line, time to process last line
            
        } else if( (int)myByte == 10 ){
            
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
            
            // we expect 8 params: 123 123 123 123 0 0 1 1
            
            if( paramCount == 8 ) {
                
                stream >> guidao[0] >> guidao[1] >> guidao[2] >> guidao[3] >> velo[0] >> velo[1] >> velo[2] >> velo[3];
                
            }
            
            // clear string for next line
            
            mySerialBuffer = "";
            
        }else{
            
            // add byte to string
            
            mySerialBuffer += myByte;
            
        }
        
    }
    
    
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    cout << guidao[0] << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
