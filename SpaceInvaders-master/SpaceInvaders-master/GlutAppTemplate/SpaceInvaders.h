#ifndef SpaceInvaders_hpp
#define SpaceInvaders_hpp

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Ships{
	
public:
	Ships(){};					//default constructor
	
	float x;					//position x-coordinate
	float y;					//position y-coordinate
	float w;					//width
	float h;					//height
	bool firing;				//true if firing				
	bool up;					//true if moving up
	bool down;					//...
	bool right;					//...
	bool left;					//...	
	float xl;					//player laser x-coordinate
	float yl;					//player laser y-coordinate
	float xe;					//enemy laser x-coordinate
	float ye;					//enemy laser y-coordinate
	bool destroyed;				//true if ship destroyed
	string movement;			//movement direction
	
	
	virtual void draw(){};
	virtual void shoot(float){};
	virtual void move(){};
	virtual bool contains(float, float){};
	virtual void moveUp(float){};
    virtual void moveDown(float){};
    virtual void moveLeft(float){};
    virtual void moveRight(float){};
  
	virtual ~Ships(){}; 
};

class Player: public Ships{		//player ship object
	float x;
	float y;
	float rate;					//float rate measurement
	
	public:
	Player();										//default constructor
	Player(float x, float y, float h, float w);		//custom construtor
	
	
	void draw();									//player ship draw function
	void shoot(float rate);							//player shoot function
	bool contains(float mx, float my);				//true if mx, my is in ship
	
	void moveUp(float rate=0.01);					//movement handlers
    void moveDown(float rate=0.01);
    void moveLeft(float rate=0.01);
    void moveRight(float rate=0.01);
    
    ~Player(){};
};


class Enemies: public Ships{						//enemy ship object
	public:
	
	Enemies(float x, float y, float w, float h, string movement);	//custom constructor
	
	void move(float rate);							//enemy movement function
	void draw();									//enemy draw function
	void shoot(float rate);							//enemy shoot function
	bool contains(float mx, float my);				//true if mx, my is in ship
	
	~Enemies(){};
};

class Game {										//game object
	int difficulty;									//variable for number of ships
	vector<Ships*> e;								//vector to store enemies
	int counter;									//general count variable
	

	public:	

	int screen;	
	Game(int difficulty);							//custom constructor
	Ships* p;										//ship pointer to player object
	void draw();									//game draw function
	void reset();									//reset function
    void drawBitmapText(char *string,float x,float y,float z);
    void drawBitmapTextsmall(char *string,float x,float y,float z);
	void scoredisplay (float posx, float posy, float posz, float space_char, int scorevar);
	double score;									//score variable
	

	~Game(){};
};


#endif
