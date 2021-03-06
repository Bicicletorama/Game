#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "player.h"


class panelUI {
    
public:
    
    
	ofxUICanvas *gui1;  
	ofxUICanvas *gui2;  
	ofxUICanvas *gui3;
    
    KinectInterface *m_kinect;
    Game *m_game;
    
    void setup(KinectInterface *m_kinect, Game *m_game)
    {
        this->m_kinect = m_kinect;
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
        gui1->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 5000.0, 1000.0, "MinBlobArea"));
        gui1->addWidgetDown(new ofxUISlider(length-xInit,dim, 0, 30, 5, "Tolerance"));
        gui1->addWidgetDown(new ofxUISlider(length-xInit,dim, 1, 10, 3, "Sensibility"));
        gui1->addWidgetDown(new ofxUISlider(length-xInit,dim, -27.0, 27.0, 0.0, "Angle"));
        
        gui1->addWidgetDown(new ofxUISpacer(length-xInit, 2));
        gui1->addWidgetDown(new ofxUILabelButton( length-xInit, false, "CAPTURE BACKGROUND", OFX_UI_FONT_MEDIUM));
        gui1->addWidgetDown(new ofxUILabelButton( length-xInit, false, "SAVE", OFX_UI_FONT_MEDIUM)); 	
        gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW MINI KINECT")); 	
        gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "SHOW CROPPED"));
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
        
		gui2->addSpacer(0, 20);
		gui2->addWidgetDown(new ofxUILabel("INTERPOLATION", OFX_UI_FONT_MEDIUM)); 
		gui2->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 4000.0, 4000.0, "FAR BOTTOM"));
		gui2->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 4000.0, 4000.0, "FAR TOP"));
        
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
        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.1, 0.99, 0.7, "FLOOR FRICTION"));
        gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 1.0, 20.0, 10, "MAX IDLE TIME"));
        
		gui3->addSpacer(0, 20);
		gui3->addWidgetDown(new ofxUILabel("RIOT", OFX_UI_FONT_MEDIUM)); 

		gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 10.0, 100.0, 30.0, "COPS MAX"));
		gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.2, 4.0, 1.0, "COPS INCREMENT RATE"));
		gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 1.0, 30.0, 15.0, "COP ADD INTERVAL"));
		gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 10.0, 100.0, 60.0, "CIVIL MAX"));
		gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.2, 4.0, 1.0, "CIVIL INCREMENT RATE"));
		gui3->addWidgetDown(new ofxUISlider(length-xInit,dim, 1.0, 30.0, 15.0, "CIVIL ADD INTERVAL"));
        gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "KNOCKOUT COP"));
        
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
            m_kinect->BLUR_AMOUNT = slider->getScaledValue();
        }
        else if(name == "MinBlobArea")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
            m_kinect->MIN_BLOB_AREA = slider->getScaledValue();
        }
        else if(name == "Tolerance")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
            m_kinect->TOLERANCE = slider->getScaledValue();
        }
        else if(name == "Sensibility")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
            m_kinect->SENSIBILITY = slider->getScaledValue();
        }
        else if(name == "Angle")
        {
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			m_kinect->setAngle(slider->getScaledValue());
        }
        else if(name == "CAPTURE BACKGROUND")
        {
            m_kinect->captureBackground(true);
        }
        else if(name == "SAVE")
        {
            save();
        } 	
        else if(name == "SHOW MINI KINECT")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_kinect->showKinect = toggle->getValue() == 1;        
        } 	
        else if(name == "SHOW CROPPED")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_kinect->showCropped = toggle->getValue() == 1;
            
        }
        else if(name == "SHOW CONTOUR")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_kinect->showContour = toggle->getValue() == 1;
            
        }
        else if(name == "TOP_RIGHT" || name == "BOTTOM_LEFT")
        {
            ofxUI2DPad * pad = (ofxUI2DPad *)gui2->getWidget("TOP_RIGHT");
            ofxUI2DPad * pad2 = (ofxUI2DPad *)gui2->getWidget("BOTTOM_LEFT");
            
            int x = pad->getScaledValue().x;
            int y = pad->getScaledValue().y;
            int w = pad2->getScaledValue().x - pad->getScaledValue().x;
            int h = pad2->getScaledValue().y - pad->getScaledValue().y;
            
            m_kinect->updateROI(x, y, w, h);
        }
        else if(name == "FAR TOP")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            
			m_kinect->FAR_TOP = slider->getScaledValue();
			m_kinect->captureBackground(true);
        }
        else if(name == "FAR BOTTOM")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            
			m_kinect->FAR_BOTTOM = slider->getScaledValue();
			m_kinect->captureBackground(true);
        }
        else if(name == "HORSE POWERS")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
            
            for(int i=0; i<TOTAL_PLAYERS; i++){
                m_game->playerList[i].HORSEPOWERS = slider->getScaledValue(); 
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
        else if(name == "COPS MAX")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			m_game->aiControl.copsStatus.max = slider->getScaledValue();
			m_game->aiControl.copsStatus.maxPerRound = slider->getScaledValue() * 0.2;
        }
        else if(name == "COPS INCREMENT RATE")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			m_game->aiControl.copsStatus.accel = slider->getScaledValue();
        }
        else if(name == "COP ADD INTERVAL")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			m_game->aiControl.copsStatus.addInterval = slider->getScaledValue() * 1000;
        }
        else if(name == "CIVIL MAX")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget; 
			m_game->aiControl.civilsStatus.max = slider->getScaledValue();
			m_game->aiControl.civilsStatus.maxPerRound = slider->getScaledValue() * 0.2;
        }
        else if(name == "CIVIL INCREMENT RATE")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			m_game->aiControl.civilsStatus.accel = slider->getScaledValue();
        }
        else if(name == "CIVIL ADD INTERVAL")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			m_game->aiControl.civilsStatus.addInterval = slider->getScaledValue() * 1000;
        }
        else if(name == "KNOCKOUT COP")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
            m_game->knocksCop = toggle->getValue();
        }
    }
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
        gui2->saveSettings("GUI/crop.xml");;
        gui3->saveSettings("GUI/box2darduino.xml");
    }
    
};
