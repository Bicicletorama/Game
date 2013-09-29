
#include "Game.h"


//--------------------------------------------------------------
void Game::setup(int _width, int _height, b2World* _world, ofArduino _arduino)
{
    width = _width;
    height = _height;
    world = _world;
    arduino = _arduino;
    
    //background
	background.loadImage("images/bicicletorama007.jpg");
    
    //players
    for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].setup(i, world);
    }
    
    //trace
	canvas.allocate(width, height, GL_RGBA);	
	canvas.begin();  
        ofClear(255, 255, 255, 0);  
    canvas.end();
    
    //start
    startGame();	
    
}

//--------------------------------------------------------------
void Game::update()
{   
    //contagem regressiva
    if (timerStartGame > 0) {
        timerStartGame--;
    } else if (timerStartGame == 0) {
        for (int i=0; i<TOTAL_PLAYERS; i++) {
            playerList[i].locked = false;
        }        
    }
    
    //players
    for (int i=0; i<TOTAL_PLAYERS; i++) {
        //playerList[i].update(arduino.getAnalog(i), arduino.getDigital(i+2));
    }
    playerList[0].update(0, 0, false);
    playerList[1].update(0, 0, false);
    playerList[2].update(0, 0, false);
    playerList[3].update(arduino.getAnalog(0), arduino.getDigital(2), true);
    /*
    list<int>* lista = arduino.getDigitalHistory(2);
    for (list<int>::iterator it = lista->begin(); it != lista->end(); it++) {
        //cout << *it << " ";
    }
    //    cout << endl;
    */
    
}

//--------------------------------------------------------------
void Game::draw() 
{
    //trace
    background.draw(0, 0);
	canvas.begin();
	{
        ofSetColor(255,255,255,3);
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
	canvas.draw(0,0);
    
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
    if (timerStartGame > 0) {
        string contagem = ofToString(timerStartGame/60 + 1);
        int scale = 60;
        ofPushStyle();
        ofPushMatrix();
        ofSetHexColor(0xffffff);
        ofScale(scale, scale);
        ofDrawBitmapString(contagem, 450/scale, 700/scale);
        ofPopMatrix();
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void Game::keyReleased(int key) 
{    
    //players keyboards extra controls
    switch(key)
    { 
        case 357: playerList[0].applyImpulse(); break; //up
        case 359: playerList[0].setDirection(0); break; //down
        case 356: playerList[0].setDirectionIncrement(-1); break; //left
        case 358: playerList[0].setDirectionIncrement(1); break; //right
            
        case 119: playerList[1].applyImpulse(); break; //w
        case 115: playerList[1].setDirection(0); break; //s
        case 97 : playerList[1].setDirectionIncrement(-1); break; //a
        case 100: playerList[1].setDirectionIncrement(1); break;//d
            
        case 121: playerList[2].applyImpulse(); break; //y
        case 104: playerList[2].setDirection(0); break; //h
        case 103: playerList[2].setDirectionIncrement(-1); break; //g
        case 106: playerList[2].setDirectionIncrement(1); break; //j
            
        case 'p': startGame(); break;
    }
}

//--------------------------------------------------------------
void Game::mouseDragged(int x, int y, int button)
{
    ofxBox2dCircle circle;
    circle.setPhysics(3.0, 0.53, 0.1);
    circle.setup(world, x, y, 20);
    circle.body->SetType(b2_staticBody);
    obstaculos.push_back(circle);
}

//--------------------------------------------------------------
void Game::startGame()
{
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].goToStartPosition(true);
    }
    
    timerStartGame = 3 * 30;
    
    canvas.begin();
        ofClear(0, 0, 0);
    canvas.end();
}

