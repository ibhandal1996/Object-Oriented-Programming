#include "App.h"
#include <iostream>
static App* singleton;

/*void explode(int value){
    
    if (!singleton->painting->complete){
        singleton->painting->advance();
        singleton->redraw();
        glutTimerFunc(32, explode, value);
    }
}*/
void move(int value){
	
    if (singleton->up){
        singleton->g->p->moveUp(0.01);
        singleton->redraw();
    }
    if (singleton->down){
        singleton->g->p->moveDown(0.01);
        singleton->redraw();
    }
    if (singleton->left){
        singleton->g->p->moveLeft(0.01);
        singleton->redraw();
    }
    if (singleton->right){
        singleton->g->p->moveRight(0.01);
        singleton->redraw();
    }
    if (singleton->up || singleton->down || singleton->left || singleton->right){
        singleton->redraw();
        
        glutTimerFunc(1, move, value);
    }
}




App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    
    singleton = this;
    mx = 0.0;
    my = 0.0;
    
    
    
    background = new TexRect("Space.png", -1, 1, 2, 2);
    g = new Game(10);							//initialize game

    up = down = left = right = false;
    
    moving = false;

}



void App::specialKeyPress(int key){
    glutIgnoreKeyRepeat(1);			//helps slow acceleration when holding down move keys
    if (key == 100){
        left = true;
       
    }
    if (key == 101){
        up = true;
    }
    if (key == 102){
        right = true;
    }
    if (key == 103){
        down = true;
    }
    redraw();
    move(1);
}

void App::specialKeyUp(int key){
    if (key == 100) {
        left = false;
    }
    if (key == 101) {
        up = false;
    }
    if (key == 102) {
        right = false;
    }
    if (key == 103) {
        down = false;
    }
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set Color
    glColor3d(1.0, 1.0, 1.0);
    
    //draw game
    g->draw();
    if(g->screen == 1)
    {
        background->draw();
        glutSwapBuffers();
    }
    if(g->screen == 2)
    {
        background->draw();
        glutSwapBuffers();
    }
    if(g->screen == 0)
    {
        background->draw();
        glutSwapBuffers();
    }
    
    glDisable(GL_TEXTURE_2D);
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
	/*if(painting->contains(x,y)){
    	explode(0);
    // Redraw the scene
    	redraw();
   }*/
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    //redraw();
}

void App::idle(){
    
        redraw();
    
}



void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        
        //delete background;
        //delete game
        delete g;
        
        exit(0);
    }
    
    if (key == ' '){
    	//fire if pressed space bar
    	g->p->firing = 1;
    	//redraw();
    	
    }
    
}

void App::keyUp(unsigned char key) {
	if (key == ' '){
    	//stop firing if released space bar
    	g->p->firing = 0;
    }
    if (key == 'r') {
    	//reset if r pressed
    	g->reset();
        g->screen = 2;
        g->score = 0;
    }
    if (key == 13)
    {
        g->screen = 1;
        g->score = 0;
    }
}


