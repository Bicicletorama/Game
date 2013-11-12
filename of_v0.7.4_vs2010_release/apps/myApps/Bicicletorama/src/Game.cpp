#include "Game.h"


//--------------------------------------------------------------
void Game::setup(ofxBox2d * _box2d, Arduino * _arduino)
{
    box2d = _box2d;
	world = box2d->getWorld();
    arduino = _arduino;

    // register the listener so that we get the events
    ofAddListener(box2d->contactStartEvents, this, &Game::contactStart);
    ofAddListener(box2d->contactEndEvents, this, &Game::contactEnd);
    
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
	
	powerUp.setup(world, true);
	powerDown.setup(world, false); 
	

	//npc
	aiControl.setup(world, &playerList);
	ofAddListener(aiControl.onWin, this, &Game::onRiotWin);
	ofAddListener(aiControl.onLose, this, &Game::onRiotLose);
	endScreenAlpha = 0;
	
	winScreen.loadImage("images/youWin.png");
	loseScreen.loadImage("images/youLose.png");
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
    
	//power change
	powerUp.update();
	if (!powerUp.enabled && ofRandom(1) < POWER_CHANGE_PERCENT_SHOW) {
		powerUp.showAt(ofRandom(WIDTH), ofRandom(HEIGHT));
	}

	powerDown.update();
	if (!powerDown.enabled && ofRandom(1) < POWER_CHANGE_PERCENT_SHOW) {
		powerDown.showAt(ofRandom(WIDTH), ofRandom(HEIGHT));
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
	aiControl.update();
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
    
	//power change
	powerUp.draw();
	powerDown.draw();

    //players
    ofSetColor(255);
	for (int i=0; i<TOTAL_PLAYERS; i++) {
        playerList[i].draw();   
    }

	//npc
	aiControl.draw();
    
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

	//tela de vitoria ou derrota
	if(endScreenAlpha>0){
		ofSetColor(255, endScreenAlpha);
		endScreen->draw(0, 0, WIDTH, HEIGHT);
	}
	
    ofPopStyle();
}

//--------------------------------------------------------------
void Game::keyReleased(int key) 
{    
    if (key == 'p') startGame();
    if (key == 'r') toggleState();
    
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
	if(button==1){
		aiControl.addCop();
	}else{
		aiControl.addCivil();
	}
}

//--------------------------------------------------------------
void Game::toggleState()
{
	if(state==RIOT) changeState(RACE);
	else changeState(RIOT);
}

//--------------------------------------------------------------
void Game::changeState(states state)
{
	this->state = state;

	if(state==RIOT){
		aiControl.start();
	}else if(state==RACE){
		aiControl.stop();
	}
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

//--------------------------------------------------------------
void Game::onRiotWin(int & n)
{
	showEndScreen(&winScreen);
}

//--------------------------------------------------------------
void Game::onRiotLose(int & n)
{
	showEndScreen(&loseScreen);
}

//--------------------------------------------------------------
void Game::showEndScreen(ofImage * image)
{
	aiControl.stop();

	endScreen = image;

	endScreenAlpha = 0;
	Tweenzor::add(&endScreenAlpha, endScreenAlpha, 255.f, 0.f, 2.f);
	Tweenzor::addCompleteListener( Tweenzor::getTween(&endScreenAlpha), this, &Game::onShowEndScreenComplete);
}

//--------------------------------------------------------------
void Game::onShowEndScreenComplete(float* arg)
{
	float delayedCall = 0;
	Tweenzor::add(&delayedCall, delayedCall, 1.f, 0.f, 6.f);
	Tweenzor::addCompleteListener( Tweenzor::getTween(&delayedCall), this, &Game::hideEndScreen);
}

//--------------------------------------------------------------
void Game::hideEndScreen(float* arg)
{
	Tweenzor::add(&endScreenAlpha, endScreenAlpha, 0.f, 0.f, 1.f);
}


//--------------------------------------------------------------
// Box2D Contact System
//--------------------------------------------------------------

void Game::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) {
		
		//power up
		checkContactStart_powerChange(e.a, e.b);
		checkContactStart_powerChange(e.b, e.a);

		//cop
		checkContactStart_cop(e.a, e.b);
		checkContactStart_cop(e.b, e.a);
	}
}

void Game::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) { 
		
		//power up
		checkContactEnd_powerChange(e.a, e.b);
		checkContactEnd_powerChange(e.b, e.a);
    }
}

void Game::checkContactStart_powerChange(b2Fixture * a, b2Fixture * b)  {

	GenericData * dataA = (GenericData*)a->GetBody()->GetUserData();
	if (dataA != NULL && dataA->name == "powerChange") {

		GenericData * dataB = (GenericData*)b->GetBody()->GetUserData();
		if (dataB != NULL && dataB->name == "bike") {

			player * p = (player*)dataB->data;
			p->addPowerChange(*(float*)dataA->data);
		}
	}
}

void Game::checkContactEnd_powerChange(b2Fixture * a, b2Fixture * b)  {

	GenericData * dataA = (GenericData *)(a->GetBody()->GetUserData());
	if (dataA != NULL && dataA->name == "powerChange") {

		GenericData * dataB = (GenericData *)(b->GetBody()->GetUserData());
		if (dataB != NULL && dataB->name == "bike") {

			player * p = (player*)dataB->data;
			p->removePowerChange(*(float*)dataA->data);
		}
	}
}

void Game::checkContactStart_cop(b2Fixture * a, b2Fixture * b)  {

	GenericData * dataA = (GenericData*)a->GetBody()->GetUserData();
	if (dataA != NULL && dataA->name == "cop") {

		GenericData * dataB = (GenericData*)b->GetBody()->GetUserData();
		if (dataB != NULL && (dataB->name == "bike" || dataB->name == "frontWheel" || dataB->name == "rearWheel")) {
			human * h = (human*)dataA->data;
			h->die();
		}
	}
}