
#include "game.h"


//--------------------------------------------------------------
void game::setup(int _width, int _height, b2World* _world, ofArduino _arduino)
{
    width = _width;
    height = _height;
    world = _world;
    arduino = _arduino;
    
    //background
	background.loadImage("images/background.jpg");
    
    //players
    for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].setup(i, world);
        playerList[i].goToStartPosition();
    }
    
    //trace
	canvas.allocate(width, height, GL_RGBA);	
	canvas.begin();  
        ofClear(255, 255, 255, 0);  
    canvas.end();
    
    //start
    locked = false;    
}

//--------------------------------------------------------------
void game::update()
{   
    //contagem regressiva
    startGameTimer = (ofGetElapsedTimeMillis() - startGameMillis) / 1000;
    
    //players
    if (!locked)
    {
        //players
        for (int i=0; i<TOTAL_PLAYERS; i++) {
            //playerList[i].update(arduino.getAnalog(i), arduino.getDigital(i+2));
        }
        playerList[0].update(0, 0, false);
        playerList[1].update(0, 0, false);
        playerList[2].update(0, 0, false);
        playerList[3].update(0, 0, false);
        //playerList[3].update(arduino.getAnalog(0), arduino.getDigital(2), true);
        /*
        list<int>* lista = arduino.getDigitalHistory(2);
        for (list<int>::iterator it = lista->begin(); it != lista->end(); it++) {
            //cout << *it << " ";
        }
        //    cout << endl;
        */
    }
    
}

//--------------------------------------------------------------
void game::draw() 
{
    ofPopStyle();
    //trace
    background.draw(0, 0);
	canvas.begin();
	{
        ofSetColor(255,255,255,2);
        background.draw(0, 0);
                
        for (int i=0; i<TOTAL_PLAYERS; i++) {
            int xx = playerList[i].x;
            int yy = playerList[i].y;
            ofSetColor(playerList[i].color, 255);
            if(ofDist(xx, yy, playerList[i].oldX, playerList[i].oldY)>1){
                
                int loop = ofRandom(10,30);
                for(int j=0; j<loop; j++){
                    int xx2 = xx + ofRandom(-5, 5);
                    int yy2 = yy + ofRandom(-5, 5);
                    if(xx2 > 0 && yy2 > 0){
                        ofCircle(xx2, yy2, 1);
                    }
                }
            }
        }		
	}
	canvas.end();
    ofSetColor(255);
	canvas.draw(0,0);
    ofPushStyle();
    
    //players
    ofSetColor(255);
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].draw();   
    }
    
    //hit
	for (int i=0; i<obstaculos.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		obstaculos[i].draw();
	}
    
    //contagem regressiva
    if (startGameTimer < 5)
    {
        float scale = 60.0;
        ofPushStyle();
        ofPushMatrix();
            ofScale(scale, scale);
            switch (startGameTimer) 
            {
                case 0:
                    ofSetHexColor(0xff0000);
                    ofDrawBitmapString("3", 350/scale, 700/scale);
                    break;
                case 1:
                    ofSetHexColor(0xff0000);
                    ofDrawBitmapString("2", 350/scale, 700/scale);
                    break;
                case 2:
                    ofSetHexColor(0xff0000);
                    ofDrawBitmapString("1", 350/scale, 700/scale);
                    break;
                case 3:
                    ofSetHexColor(0xffff00);
                    ofDrawBitmapString("E", 350/scale, 700/scale);
                    break;
                case 4:
                    ofSetHexColor(0x00ff00);
                    ofDrawBitmapString("JA", 50/scale, 700/scale);
                    locked = false;
                    break;
            }
        ofPopMatrix();
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void game::keyReleased(int key) 
{    
    if (key == 'p') startGame();
    
    if (!locked)
    {
        //players keyboards extra controls
        switch(key)
        { 
            case 357: playerList[0].applyImpulse(); break; //up
            case 359: playerList[0].setDirection(0); break; //down
            case 356: playerList[0].setDirectionIncrement(-1); break; //left
            case 358: playerList[0].setDirectionIncrement(1); break; //right
            
            case 'w': playerList[1].applyImpulse(); break;
            case 's': playerList[1].setDirection(0); break;
            case 'a': playerList[1].setDirectionIncrement(-1); break;
            case 'd': playerList[1].setDirectionIncrement(1); break;
            
            case 'y': playerList[2].applyImpulse(); break;
            case 'h': playerList[2].setDirection(0); break;
            case 'g': playerList[2].setDirectionIncrement(-1); break;
            case 'j': playerList[2].setDirectionIncrement(1); break;
            
            case 'Y': playerList[3].applyImpulse(); break;
            case 'H': playerList[3].setDirection(0); break;
            case 'G': playerList[3].setDirectionIncrement(-1); break;
            case 'J': playerList[3].setDirectionIncrement(1); break;
        }
    }
}

//--------------------------------------------------------------
void game::mouseDragged(int x, int y, int button)
{
    /*ofxBox2dCircle circle;
    circle.setPhysics(3.0, 0.53, 0.1);
    circle.setup(world, x, y, 20);
    circle.body->SetType(b2_staticBody);
    obstaculos.push_back(circle);*/
}

//--------------------------------------------------------------
void game::startGame()
{
    locked = true;
    startGameMillis = ofGetElapsedTimeMillis();
    
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].goToStartPosition();
    }
    
    canvas.begin();
        ofClear(0, 0, 0);
    canvas.end();
}

