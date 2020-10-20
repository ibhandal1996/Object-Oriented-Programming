#ifndef textures_h
#define textures_h

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif

#include "SOIL.h"
#include "RgbImage.h"
class texture {
	float x;
    float y;
    float w;
    float h;
    GLuint texture_id;
    int rows;
    int cols;
    int curr_row;
    int curr_col;
    public:
    texture(const char*);
    
    void draw();
};




#endif
