
#include "stats.h"


void stats::setup()
{
    width = 300;
    height = 100;
    
    max = 50;
    
    minMilesecondsInterval = 100;
    
    color[0] = 0x22F960;
    color[1] = 0xFFF220;
    color[2] = 0xF9222B;
    color[3] = 0x22D3F9;
    
    for(int i=0; i<TOTAL_VEL; i++){
        _v1[i] = 1;
        _v2[i] = 1;
        _v3[i] = 1;
        _v4[i] = 1;
    }
}

void stats::update(player playerList[TOTAL_PLAYERS]) 
{
    if (ofGetElapsedTimeMillis()-lastTime<minMilesecondsInterval) return;
    lastTime = ofGetElapsedTimeMillis();
    
    max = 1;
    
    float v1 = playerList[0].getVelocity();
    float v2 = playerList[1].getVelocity();
    float v3 = playerList[2].getVelocity();
    float v4 = playerList[3].getVelocity();
    
    for(int i=TOTAL_VEL-1; i>=0; i--){
        //cout << _v1[i] << ", ";
        if(i==0){
            _v1[i] = v1;
            _v2[i] = v2;
            _v3[i] = v3;
            _v4[i] = v4;
        }else{
            _v1[i] = _v1[i-1];
            _v2[i] = _v2[i-1];
            _v3[i] = _v3[i-1];
            _v4[i] = _v4[i-1];
        }
        
        if(_v1[i]>max) max = _v1[i];
        if(_v2[i]>max) max = _v2[i];
        if(_v3[i]>max) max = _v3[i];
        if(_v4[i]>max) max = _v4[i];
    }
    cout << endl;
}

void stats::draw()
{
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(500, 600, 0.0);
    ofSetHexColor(0x111111);
    ofRect(0,0,width, height);
    
    float pag = width / TOTAL_VEL;
    float pagAtual;
    float pagProx;
    cout << _v1[0] <<endl;
    for(int i=0; i<TOTAL_VEL-1; i++)
    {
        pagAtual = pag*i;
        pagProx = pag*(i+1);
                
        ofSetHexColor(color[0]);
        ofLine(pagAtual, height-(_v1[i]/max*height), pagProx, height-(_v1[i+1]/max*height));
        
        ofSetHexColor(color[1]);
        ofLine(pagAtual, height-(_v2[i]/max*height), pagProx, height-(_v2[i+1]/max*height));
        
        ofSetHexColor(color[2]);
        ofLine(pagAtual, height-(_v3[i]/max*height), pagProx, height-(_v3[i+1]/max*height));
        
        ofSetHexColor(color[3]);
        ofLine(pagAtual, height-(_v4[i]/max*height), pagProx, height-(_v4[i+1]/max*height));
    }
    
    ofPopMatrix();
    ofPopStyle();
}
