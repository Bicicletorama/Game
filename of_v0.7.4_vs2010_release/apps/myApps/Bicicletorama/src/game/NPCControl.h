#pragma once

#include "ofMain.h"
#include "ofxTweenzor.h"
#include "human.h"
#include "cop.h"
#include "bomb.h"
#include "civil.h"

class NPCControl{
public:
	void setup(b2World * world, player (* playerList)[TOTAL_PLAYERS])
	{
		this->playerList = playerList;
		this->world = world;

		//bomb
		#ifdef TARGET_OPENGLES
		bombCanvas.allocate(WIDTH, HEIGHT, GL_RGBA);
		ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";        
		#else
		bombCanvas.allocate(WIDTH, HEIGHT, GL_RGBA32F_ARB);
		#endif

		enabled = false;
		
		MIN_ADD_TIME_COP = 20000;
		MIN_ADD_TIME_CIVIL = 10000;
	}

	void update()
	{
		//humans
		for (int i=0; i<humans.size(); i++) {
			if(humans[i]->hasComplete()){
				delete humans[i];
				humans.erase(humans.begin() + i);
			}else{
				humans[i]->update();
			}
		}

		if(enabled){
			if(ofGetElapsedTimeMillis() - lastTimeAddCop > MIN_ADD_TIME_COP) addCops();
			if(ofGetElapsedTimeMillis() - lastTimeAddCivil > MIN_ADD_TIME_CIVIL) addCivils();
		}

		//bomb
		for(int i=bombs.size()-1; i >= 0; i--){
			if(bombs[i]->hasComplete()){
				delete bombs[i];
				bombs.erase(bombs.begin() + i);
			}else{
				bombs[i]->update();
			}
		}
	}

	void draw()
	{
		//humans
		for (int i=0; i<humans.size(); i++) {
			humans[i]->draw();
		}

		//bomb
		bombCanvas.begin();
		ofSetColor(255, 255, 255, 10);
		ofRect(0, 0, WIDTH, HEIGHT);
		ofSetColor(255);
		for(int i=0; i < bombs.size(); i++){
			bombs[i]->draw();
		}
		bombCanvas.end();
		bombCanvas.draw(0, 0);
	}

	void start()
	{
		enabled = true;
		addCops();
		addCivils();
	}

	void stop()
	{
		enabled = false;
		//humans
		for (int i=0; i<humans.size(); i++) {
			humans[i]->leave();
		}
	}

	void addCops()
	{
		int totalCops = ofRandom(3) + 2;
		for(int i=0; i<totalCops; i++) addCop();
	}

	void addCop()
	{
		lastTimeAddCop = ofGetElapsedTimeMillis() + ofRandom(2000);
		cop * c = new cop();
		ofAddListener(c->onAttack, this, &NPCControl::onCopAttack);
		c->setup(world, playerList);
		humans.push_back((human *)c);
	}

	void addCivils()
	{
		int totalCivil = ofRandom(5) + 3;
		for(int i=0; i<totalCivil; i++) addCivil();
	}

	void addCivil()
	{
		lastTimeAddCivil = ofGetElapsedTimeMillis() + ofRandom(2000);
		lastTimeAddCivil = ofGetElapsedTimeMillis();
		civil * c = new civil();
		c->setup(world, playerList);
		humans.push_back((human *)c);
	}

private:
	bool enabled;

    double lastTimeAddCivil;
    double lastTimeAddCop;
	
	int MIN_ADD_TIME_COP;
	int MIN_ADD_TIME_CIVIL;

    b2World * world;

    player (* playerList)[TOTAL_PLAYERS];

    vector <human*>	humans;
	
	vector<bomb*> bombs;
	ofFbo bombCanvas;

	void onCopAttack(attack & a)
	{
		bomb * b = new bomb();
		b->setup(a.startX, a.startY, a.endX, a.endY);
		bombs.push_back(b);
	}
    
};
