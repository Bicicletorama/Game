#pragma once

#include "ofMain.h"
#include "ofxTweenzor.h"
#include "human.h"
#include "cop.h"
#include "bomb.h"
#include "civil.h"

struct NPCStatus{
	float max;
	int maxPerRound;
	float initialAccel;
	float deAccel;
	float count;
	int round;
	float addInterval;
};

class NPCControl{
public:
	NPCStatus copsStatus;
	NPCStatus civilsStatus;

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

		copsStatus.max = 30;
		civilsStatus.max = 60;

		copsStatus.maxPerRound = copsStatus.max * 0.2;
		civilsStatus.maxPerRound = civilsStatus.max * 0.2;

		copsStatus.initialAccel = 0.5;
		civilsStatus.initialAccel = 1;

		copsStatus.deAccel = 0.001;
		civilsStatus.deAccel = 0.001;
		
		copsStatus.addInterval = 15000;
		civilsStatus.addInterval = 15000;
	}

	void update()
	{
		copsStatus.count = 0;
		civilsStatus.count = 0;

		//humans
		for (int i=0; i<humans.size(); i++) {
			if(humans[i]->hasComplete()){
				delete humans[i];
				humans.erase(humans.begin() + i);
			}else{
				if(humans[i]->type==humans[i]->COP){
					((cop *)humans[i])->update();
					copsStatus.count++;
				}else if(humans[i]->type==humans[i]->CIVIL){
					((civil *)humans[i])->update();
					civilsStatus.count++;
				}
			}
		}

		if(enabled){
			if(ofGetElapsedTimeMillis() - lastTimeAddCop > copsStatus.addInterval) addCops();
			if(ofGetElapsedTimeMillis() - lastTimeAddCivil > civilsStatus.addInterval) addCivils();
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
			if(humans[i]->type==humans[i]->COP){
				((cop *)humans[i])->draw();
			}else if(humans[i]->type==humans[i]->CIVIL){
				((civil *)humans[i])->draw();
			}
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
		copsStatus.round = 0;
		civilsStatus.round = 0;
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
		copsStatus.round++;
		int totalCops = ofRandom(2) + ((copsStatus.initialAccel - (copsStatus.round * copsStatus.deAccel)) * copsStatus.round);
		totalCops = min(totalCops, copsStatus.maxPerRound);
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
		civilsStatus.round++;
		int totalCivil = ofRandom(2) + ((civilsStatus.initialAccel - (civilsStatus.round * civilsStatus.deAccel)) * civilsStatus.round);
		totalCivil = min(totalCivil, civilsStatus.maxPerRound);
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
		ofAddListener(b->onExplode, this, &NPCControl::onBombExplode);
		b->setup(a.startX, a.startY, a.endX, a.endY);
		bombs.push_back(b);
	}

	void onBombExplode(ofVec2f & pos)
	{
		for (int i=0; i<humans.size(); i++) {
			if(ofDistSquared(humans[i]->x, humans[i]->y, pos.x, pos.y)<10000){//100px
				humans[i]->die();
			}
		}
	}
    
};
