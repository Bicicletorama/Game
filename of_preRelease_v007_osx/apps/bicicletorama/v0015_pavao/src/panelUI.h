#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "player.h"


class panelUI {
    
public:
    
    
	ofxUICanvas *gui1;  
	ofxUICanvas *gui2;  
	ofxUICanvas *gui3;
    
    kinect *m_kinect;
    arduino *m_arduino;
    game *m_game;
    
    void setup(kinect *m_kinect, arduino *m_arduino, game *m_game){
        this->m_kinect = m_kinect;
        this->m_arduino = m_arduino;
        this->m_game = m_game;
        
        setGUI1();
        setGUI2();
        setGUI3();
        
        gui1->loadSettings("GUI/settings.xml");
        gui1->setVisible(false);
        
        gui2->loadSettings("GUI/crop.xml");
        gui2->setVisible(false);
        
        gui3->loadSettings("GUI/box2darduino.xml");
        gui3->setVisible(false);
    }
    
    void setGUI1()
    {
        float dim = 16; 
        float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
        float length = 455-xInit; 
        
        gui1 = new ofxUICanvas(0, 0, length+xInit, ofGetHeight()); 
        gui1->addWidgetDown(new ofxUILabel("BICICLETORAMA", OFX_UI_FONT_LARGE)); 
        gui1->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_MEDIUM)); 
        
        gui1->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
        gui1->addWidgetDown(new ofxUILabel("MAPPING", OFX_UI_FONT_MEDIUM)); 
        gui1->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 100.0, 50, "Blur"));
        gui1->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 20.0, 0, "Sizer")); 	 
        gui1->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 2000.0, 50.0, 100.0, "BlobSize")); 
        gui1->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, m_kinect->nearThreshold, m_kinect->farThreshold, "FarNear")); 	
        
        gui1->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
        gui1->addWidgetDown(new ofxUILabelButton( length-xInit, false, "SAVE", OFX_UI_FONT_MEDIUM)); 	
        gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW MINI KINECT")); 	
        gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW CROPPED")); 	
        gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW DEPTH")); 	
        gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW CONTOUR")); 	
        
        
        ofAddListener(gui1->newGUIEvent,this,&panelUI::guiEvent);
    }
    
    
    void setGUI2()
    {
        float dim = 16; 
        float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
        float length = 255-xInit; 
        
        gui2 = new ofxUICanvas(465+xInit, 0, length+xInit, ofGetHeight()); 
        gui2->addWidgetDown(new ofxUILabel("CROP", OFX_UI_FONT_MEDIUM)); 
        
        gui2->addWidgetDown(new ofxUI2DPad(length-xInit,120, ofPoint(0,640),  ofPoint(0,480), ofPoint(m_kinect->quadCropCorners[0].x, m_kinect->quadCropCorners[0].y), "TOP_RIGHT"));
        gui2->addWidgetDown(new ofxUI2DPad(length-xInit,120, ofPoint(0,640),  ofPoint(0,480), ofPoint(m_kinect->quadCropCorners[3].x, m_kinect->quadCropCorners[3].y), "BOTTOM_LEFT"));
        
        ofAddListener(gui2->newGUIEvent,this,&panelUI::guiEvent);
    }
    
    
    void setGUI3()
    {
        
        
        float dim = 16; 
        float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
        float length = 255-xInit; 
        
        gui3 = new ofxUICanvas(465+xInit+length+xInit+10, 0, length+xInit, ofGetHeight()); 
        gui3->addWidgetDown(new ofxUILabel("BOX2D", OFX_UI_FONT_MEDIUM)); 
        
        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 10.0, 200.0, 100, "HORSE POWER"));
        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, PI/2, PI/2.5, "MAX STEER ANGLE"));
        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.1, 0.99, 0.7, "FLOOR FRICTION"));
        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 1.0, 20.0, 10, "MAX IDLE TIME"));
        
        
        
        gui3->addWidgetDown(new ofxUILabel("ARDUINO", OFX_UI_FONT_MEDIUM)); 
        
        vector<string> names; 
        names.push_back("/dev/usbmodemfd121");
        names.push_back("/dev/tty.usbmodemfa131");	
        gui3->addWidgetDown(new ofxUIRadio( dim, dim, "USB", names, OFX_UI_ORIENTATION_VERTICAL));
        
        gui3->addWidgetDown(new ofxUILabel("PORTAS ANALOGICAS", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetDown(new ofxUINumberDialer(0, 5, 0, 0, "ANALOG 0", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetRight(new ofxUINumberDialer(0, 5, 2, 0, "ANALOG 1", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetRight(new ofxUINumberDialer(0, 5, 4, 0, "ANALOG 2", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetRight(new ofxUINumberDialer(0, 5, 5, 0, "ANALOG 3", OFX_UI_FONT_MEDIUM)); 
        
        
        gui3->addWidgetDown(new ofxUILabel("PORTAS DIGITAIS", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetDown(new ofxUINumberDialer(2, 13, 2, 0, "DIGITAL 0", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetRight(new ofxUINumberDialer(2, 13, 4, 0, "DIGITAL 1", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetRight(new ofxUINumberDialer(2, 13, 6, 0, "DIGITAL 2", OFX_UI_FONT_MEDIUM)); 
        gui3->addWidgetRight(new ofxUINumberDialer(2, 13, 8, 0, "DIGITAL 3", OFX_UI_FONT_MEDIUM)); 

        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 1023.0, 490, "POTENCIOMETRO MIDDLE"));
        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 1.0, 511.0, 300, "POTENCIOMETRO RANGE"));
        
        
        ofAddListener(gui3->newGUIEvent,this,&panelUI::guiEvent);
    }
    
    void keyPressed(int key)
    {   
        switch (key) 
        {
            case ' ':
                gui1->toggleVisible();
                gui2->toggleVisible();
                gui3->toggleVisible();
                break;	
            case 's':
                save();
                break;
        }
    }
    
    
    void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName(); 
        int kind = e.widget->getKind(); 
        cout << "got event from: " << name << endl; 	
        
        if(name == "Blur")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            m_kinect->blur = slider->getScaledValue(); 
        }
        else if(name == "Sizer")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            m_kinect->sizer = slider->getScaledValue(); 
        }
        else if(name == "BlobSize")
        {
            ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget; 
            m_kinect->minBlobSize = slider->getScaledValueLow(); 
            m_kinect->maxBlobSize = slider->getScaledValueHigh(); 
        }
        else if(name == "FarNear")
        {
            ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget; 
            m_kinect->farThreshold = slider->getScaledValueLow(); 
            m_kinect->nearThreshold = slider->getScaledValueHigh(); 
        }
        else if(name == "SAVE")
        {
            save();
        } 	
        else if(name == "SHOW MINI KINECT")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_kinect->showRawKinect = toggle->getValue() == 1;        
        } 	
        else if(name == "SHOW CROPPED")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_kinect->showCropped = toggle->getValue() == 1;
            
        }
        else if(name == "SHOW DEPTH")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_kinect->debugKinect = toggle->getValue() == 1;
            
        }
        else if(name == "SHOW CONTOUR")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_kinect->showContour = toggle->getValue() == 1;
            
        }
        else if(name == "TOP_RIGHT")
        {
            ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
            m_kinect->quadCropCorners[0].x = pad->getScaledValue().x;
            m_kinect->quadCropCorners[0].y = pad->getScaledValue().y;
            
            m_kinect->quadCropCorners[1].y = pad->getScaledValue().y;
            m_kinect->quadCropCorners[3].x = pad->getScaledValue().x;
        }
        else if(name == "BOTTOM_LEFT")
        {
            ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
            m_kinect->quadCropCorners[2].x = pad->getScaledValue().x;
            m_kinect->quadCropCorners[2].y = pad->getScaledValue().y;
            
            m_kinect->quadCropCorners[1].x = pad->getScaledValue().x;
            m_kinect->quadCropCorners[3].y = pad->getScaledValue().y;
        }
        else if(name == "HORSE POWERS")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            
            for(int i=0; i<TOTAL_PLAYERS; i++){
                m_game->playerList[i].HORSEPOWERS = slider->getScaledValue(); 
            }
            
        }
        else if(name == "MAX STEER ANGLE")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            for(int i=0; i<TOTAL_PLAYERS; i++){
                m_game->playerList[i].MAX_STEER_ANGLE = slider->getScaledValue(); 
            }
        }
        else if(name == "FLOOR FRICTION")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            for(int i=0; i<TOTAL_PLAYERS; i++){
                m_game->playerList[i].FLOOR_FRICTION = slider->getScaledValue(); 
            }
        }
        else if(name == "MAX IDLE TIME")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;  
            for(int i=0; i<TOTAL_PLAYERS; i++){
                m_game->playerList[i].MAX_IDLE_TIME = slider->getScaledValue() * 1000; 
            }
        }
        else if(name == "ANALOG 0")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            m_arduino->analog[0] = dialer->getValue(); 
        }
        else if(name == "ANALOG 1")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            m_arduino->analog[1] = dialer->getValue(); 
        }
        else if(name == "ANALOG 2")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            m_arduino->analog[2] = dialer->getValue(); 
        }
        else if(name == "ANALOG 3")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            //m_arduino->analog[3] = dialer->getValue(); 
        }
        else if(name == "DIGITAL 0")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            //m_arduino->digital[0] = dialer->getValue(); 
        }
        else if(name == "DIGITAL 1")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            //m_arduino->digital[1] = dialer->getValue(); 
        }
        else if(name == "DIGITAL 2")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            //m_arduino->digital[2] = dialer->getValue(); 
        }
        else if(name == "DIGITAL 3")
        {
            ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget; 
            //m_arduino->digital[3] = dialer->getValue(); 
        }
        else if(name == "POTENCIOMETRO MIDDLE")
        {
            ofxUISlider *dialer = (ofxUISlider *) e.widget; 
            m_arduino->POTENCIOMETRO_MIDDLE = dialer->getScaledValue(); 
        }
        else if(name == "POTENCIOMETRO RANGE")
        {
            ofxUISlider *dialer = (ofxUISlider *) e.widget; 
            m_arduino->POTENCIOMETRO_RANGE = dialer->getScaledValue(); 
        }
    }
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
        gui2->saveSettings("GUI/crop.xml");;
        gui3->saveSettings("GUI/box2darduino.xml");
    }
    
};
