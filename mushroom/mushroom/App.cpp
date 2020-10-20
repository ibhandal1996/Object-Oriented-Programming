#include "App.h"

static App* singleton; // From example

void makeImage(int value)
{
    if(!singleton->Mushroom->ifDone())
    {
        singleton->Mushroom->animate();
        singleton->redraw();
        glutTimerFunc(32, makeImage, value);
    }
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h)
{
    // Initialize state variables
    singleton = this;
    mx = 0.0;
    my = 0.0;

    Mushroom = new TexRect("/home/iqbal/Desktop/mushroom/mushroom.bmp", 1, 1, -0.25, 0.25, 0.5, 0.5);
}

void App::draw() 
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3d(1.0, 1.0, 1.0);

    Mushroom->draw();

    glDisable(GL_TEXTURE_2D);

    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y)
{
    // Update app state
    mx = x;
    my = y;

    if(!Mushroom->ifExplode() && Mushroom->contains(mx, my))
    {
        Mushroom->explode("/home/iqbal/Desktop/mushroom/fireball.bmp", 6, 6);
        makeImage(0);
    } 
}

void App::keyPress(unsigned char key) 
{
    if (key == 27){
        delete Mushroom;
        exit(0);
    }else if(key == 'r'){
        Mushroom->restart("/home/iqbal/Desktop/mushroom/mushroom.bmp", 1, 1);
        redraw();
    }
}