#include "SpaceInvaders.h"
#include <stdio.h>


using namespace std;
char key;

Player::Player(): Ships(){	//default constructor
	x = 0.0;
	y = 0.0;
	w = 0.25;
	h = 0.25;
	xl = x;
	yl = y;
	
	firing = false;
}

Player::Player(float x, float y, float h, float w): Ships() {	//custom constructor
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	
	xl = x;
	yl = y;
	
	firing = false;
}

void Player::draw(){
	glColor3d(1.0,0.0,1.0);										//draw triangle
	glBegin (GL_POLYGON);
		glVertex2f(x-(w/2), y-h);
		glVertex2f(x+(w/2), y-h);
		glVertex2f(x, y);
	glEnd();
	if(firing){													//draw lasers
	glColor3d(0.0,1.0,0.0);
		glBegin (GL_LINES);
			glVertex2f(xl,yl);
			glVertex2f(xl,(yl-0.1));
		glEnd();
		shoot(0.1);
	}
}

void Player::shoot(float rate){									//function to handle lasers
		
		firing = true;
		yl += rate;
		if(yl>1.0){												//reset lasers when at end of screen
			yl=y;
			xl=x;
		}
}

bool Player::contains(float mx, float my){						
	 return mx >= x && mx <= x+w && my <= y && my >= y - h;
}

void Player::moveUp(float rate){
    if(y<1.0){
    	y += rate;
    }
}
void Player::moveDown(float rate){
    if((y-h)>-1.0){
    	y -= rate;
	}
}
void Player::moveLeft(float rate){
    if((x-(w/2))>-1.0){
    	x -= rate;
    }
}
void Player::moveRight(float rate){
    if((x+(w/2))<1.0){	
    	x += rate;
    }
}

Enemies::Enemies(float x, float y, float w, float h, string movement): Ships(){			//custom constructor
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	
	this->xe = x + (w/2);																
	this->ye = y + (h/2);
	
	this->destroyed = false;
	this->movement = movement;
}

void Enemies::draw(){																	//draw enemy blocks
	glColor3d(1.0,0.0,0.0);
	glBegin (GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x+w,y);
		glVertex2f(x+w,y-h);
		glVertex2f(x,y-h);
	glEnd();
	move(0.019);																			//call move function
	glColor3d(1.0,0.0,0.5);																//draw enemy lasers
		//glBegin (GL_LINES);
		//	glVertex2f(xe,ye);
		//	glVertex2f(e,(ye-0.1));
		//glEnd();																	//call shoot function
}

void Enemies::move(float rate){															//enemy move function
	if(y>1.0){
		movement = "down";
	}
	if(movement=="down"){
		y -= rate;
	}
	
}

void Enemies::shoot(float rate) {														//enemy shoot function
	ye -= rate;
	if(ye < -1.0) {
		xe = x + (w/2);
		ye = y + (h/2);
	} 
}

bool Enemies::contains(float mx, float my){
	 return mx >= x && mx <= x+w && my <= y && my >= y - h;
}

Game::Game(int difficulty){																//general game constructor
	p = new Player(0.0, 0.0, 0.15, 0.15);												//initialize new player object
	for(int i=0; i<difficulty; i++) {													//creating two rows of enemies
		e.push_back(new Enemies(-1.0 + (i*(2.0/difficulty)), 1.2, 0.1, 0.1, "down"));
		e.push_back(new Enemies(-1.0 + (i*(2.0/difficulty)), 1.2, 0.1, 0.1, "down"));
	}
	this->difficulty = difficulty;														//difficulty variable changes amount of enemies
	this->counter = 0;	
	screen = 2;											//counter for counting enemies destroyed
	
}

void Game::draw(){
	
	switch(screen)
	{
		case 0:																	//game over
		{
			glColor3d(1.0,0.0,0.0);
			drawBitmapText("YOU SUCK! GAME OVER!]", -0.5 ,0.5,0);

			scoredisplay(.8, 0.4, 0, 0.1, score);
		
			drawBitmapText("Score:]", -0.5 ,0.4,0);
			drawBitmapText("PRESS R TO RESART GAME]", -0.5 ,0.3,0);
			//glutSwapBuffers();
			break;
			
		}
		case 1:
		{
			
			if(!(p->destroyed))
			{	
																		//draw player if not destroyed
				p->draw();
				
			}
			for (int i=0; i<(difficulty*2); i++) {											//if hit by enemy laser, destroy player
				if(p->contains(e[i]->x, e[i]->y)) {
					p->destroyed = true;
					screen = 0;
				}
				if(e[i]->destroyed == false){													//if not destroyed, draw enemies
				e[i]->draw();
				}
				if(e[i]->y < -1)
				{
					reset();
				}
				if((e[i]->contains(p->xl,p->yl)) && (e[i]->destroyed==false)){					//if hit by player laser...
					score += 100;															//...add 100 to score
					e[i]->destroyed = true;														//...destroy enemy
					e[i]->ye = -1.0;															//cancel laser
					e[i]->xe = -1.0;
					counter++;																	//counter to track number of destroyed enemies	
				}
				drawBitmapText("SCORE:]", -1.0 ,-1.0,0);
				scoredisplay(0,-1,0, 0.1, score);
			}
			if (counter==(difficulty*2)) {														//if counter equals number of enemies...
				reset();																		//...call reset function
			}
			
			break;
		}	
		case 2:
		{
			glColor3d(0.0,0.0,0.0);
			drawBitmapText("Space Invaders]", -0.3 ,0.1,0);
			drawBitmapText("Press Enter to Start]", -0.3 ,0.0,0);
			drawBitmapTextsmall("kinda]", 0.2 ,0.1,0);
			glColor3d(1.0,1.0,1.0);
			drawBitmapTextsmall("By: Jason Block and Iqbal Bhandal]", -1.0 ,-0.99,0);
			break;
		
		}
	}	
		
}

void Game::reset(){		
		//cout << "reset" << endl;																//reset function
		p->destroyed = false;															//reset player
		p->x = 0;
		p->y = -.8;															
		e.clear();																		//clear enemy vector
		counter = 0;																	//reset counter
		for(int i=0; i<difficulty; i++) {												//reset enemy vector
		e.push_back(new Enemies(-1.0 + (i*(2.0/difficulty)), 1.2, 0.1, 0.1, "down"));
		e.push_back(new Enemies(-1.0 + (i*(2.0/difficulty)), 1.2, 0.1, 0.1, "down"));
		}
}

void Game::drawBitmapText(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != ']'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void Game::drawBitmapTextsmall(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != ']'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}


void Game::scoredisplay (float posx, float posy, float posz, float space_char, int scorevar)
{
        float j=0,k;
		int p;
        GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
        
        p = scorevar;
        j = 0;
        k = 0; 
        while(p > 9)
        {
            k = p % 10;
            glRasterPos3f ((posx-(j*space_char)),posy, posz);    
            glutBitmapCharacter(font_style1,48+k);
            j++;
            p /= 10;
        }
            glRasterPos3f ((posx-(j*space_char)), posy, posz);    
            glutBitmapCharacter(font_style1,48+p);
       
}