
#ifndef bicicletorama_Game_h
#define bicicletorama_Game_h


#include "ofMain.h"
#include "ofxBox2d.h"
#include "Player.h"


#define TOTAL_PLAYERS 4

class Game {
    
public:
    
    void setup(int _width, int _height, b2World* _world, ofArduino _arduino);
    void update();
    void draw();
    
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);  
    
private:
    
    int width;
    int height;
    b2World* world;
    ofArduino arduino;
    
    void startGame();
    int timerStartGame;
    
    ofImage background;
    ofFbo canvas;    
    
    Player playerList[TOTAL_PLAYERS];
    vector <ofxBox2dCircle>	obstaculos;
    
};


#endif
