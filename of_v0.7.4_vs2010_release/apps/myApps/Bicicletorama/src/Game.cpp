#include "Game.h"


//--------------------------------------------------------------
void Game::setup(b2World * _world, Arduino * _arduino)
{
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
	canvas.allocate(WIDTH, HEIGHT, GL_RGBA);
	canvas.begin();  
        ofClear(255, 255, 255, 0);  
    canvas.end();

	//bomb
	#ifdef TARGET_OPENGLES
	bombCanvas.allocate(WIDTH, HEIGHT, GL_RGBA);
	ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";        
	#else
	bombCanvas.allocate(WIDTH, HEIGHT, GL_RGBA32F_ARB);
	#endif
    
    //largada
    largada.addFile("images/largada/1.png");
    largada.addFile("images/largada/2.png");
    largada.addFile("images/largada/3.png");
    largada.addFile("images/largada/4.png");
    largada.addFile("images/largada/5.png");
    
    cabecas.addFile("images/largada/cabecas/1.png");
    cabecas.addFile("images/largada/cabecas/2.png");
    cabecas.addFile("images/largada/cabecas/3.png");
    cabecas.addFile("images/largada/cabecas/4.png");
    cabecas.addFile("images/largada/cabecas/5.png");
    cabecas.addFile("images/largada/cabecas/6.png");
    cabecas.addFile("images/largada/cabecas/7.png");
    
    //start
    locked = false;    
    
    //timer
    lastGameTimer = -1;
	
}

//--------------------------------------------------------------
void Game::update()
{
    //contagem regressiva
    startGameTimer = (ofGetElapsedTimeMillis() - startGameMillis) / 1000;

    //playSound
    if (startGameTimer < 5) {
        if(lastGameTimer!=startGameTimer){
            lastGameTimer = startGameTimer;
            sound::playAlerta();
        }
    }
    
    //players
    if (!locked)
    {
        //players
        for (int i = 0; i < TOTAL_PLAYERS; i++) {
            
			if(arduino->connected){
				int totalImpulses = arduino->getImpulse(i);
				for (int j = 0; j < totalImpulses; j++) {
					playerList[i].applyImpulse();
				}
            
				playerList[i].setDirection( arduino->getDirection(i) );
			}
            
            playerList[i].update();
        }
    }

	//npc
	for (int i=0; i<humans.size(); i++) {
		humans[i]->update();
	}
    
	//bomb
	for(int i=bombs.size()-1; i >= 0; i--){
		if(bombs[i].hasComplete()){
			bombs.erase(bombs.begin() + i);
		}else{
			bombs[i].update();
		}
	}
}

//--------------------------------------------------------------
void Game::draw() 
{
    ofPushStyle();
    
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
    
    //players
    ofSetColor(255);
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].draw();   
    }
    
    //obstaculos
	for (int i=0; i<obstaculos.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		obstaculos[i].draw();
	}
    
    //contagem regressiva
    if (startGameTimer < 5)
    {
        float scale = 60.0;
                
        largada.setCurrentFrame(startGameTimer);
        largada.draw();
        
        if (startGameTimer < 4) {
            cabecas.setCurrentFrame(currentCabeca);
            cabecas.draw();
        }
        
        if (startGameTimer == 4) {
            locked = false;
        }
    }

	//npc
	for (int i=0; i<humans.size(); i++) {
		humans[i]->draw();
	}

	//bomb
	bombCanvas.begin();
	ofSetColor(255, 255, 255, 10);
    ofRect(0, 0, WIDTH, HEIGHT);
	ofSetColor(255);
	for(int i=0; i < bombs.size(); i++){
		bombs[i].draw();
	}
	bombCanvas.end();
	bombCanvas.draw(0, 0);
	
    ofPopStyle();
}

//--------------------------------------------------------------
void Game::keyReleased(int key) 
{    
    if (key == 'p') startGame();
    
    if (!locked)
    {
        //players keyboards extra controls
        switch(key)
        { 
            case OF_KEY_UP: playerList[0].applyImpulse(); break;
			case OF_KEY_DOWN: playerList[0].setDirection(0); break;
            case OF_KEY_LEFT: playerList[0].setDirectionIncrement(-1); break;
			case OF_KEY_RIGHT: playerList[0].setDirectionIncrement(1); break;
            
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
void Game::mouseDragged(int x, int y, int button)
{
    if (BOX2D_CLICK_DRAW)
    {
        ofxBox2dCircle circle;
        circle.setPhysics(3.0, 0.53, 0.1);
        circle.setup(world, x, y, 20);
        circle.body->SetType(b2_staticBody);
        obstaculos.push_back(circle);
    }
}

//--------------------------------------------------------------
void Game::mousePressed(int x, int y, int button)
{
    cop * c = new cop();
    ofAddListener(c->onAttack, this, &Game::onCopAttack);
    c->setup(world, &playerList);
    humans.push_back((human *)c);
}

//--------------------------------------------------------------
void Game::startGame()
{
    locked = true;
    startGameMillis = ofGetElapsedTimeMillis();
    currentCabeca = floor(ofRandom(1,8));
    
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].goToStartPosition();
    }
    
    canvas.begin();
        ofClear(0, 0, 0);
    canvas.end();
}

void Game::onCopAttack(attack & a)
{
	bomb b;
	b.setup(a.startX, a.startY, a.endX, a.endY);
	bombs.push_back(b);
}
