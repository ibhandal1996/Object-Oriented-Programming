#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "SpaceInvaders.h"
#include "TexRect.h"

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
    
    

public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void keyUp(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    
    void specialKeyPress(int key);
    
    void specialKeyUp(int key);
    
    void idle();
    
    Game* g;
    TexRect* background;
    
    bool up;
    bool down;
    bool left;
    bool right;
    bool firing;
    bool moving;

    
    //TexRect* background;
};

#endif
