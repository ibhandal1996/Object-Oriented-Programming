#ifndef TexRect_h
#define TexRect_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "RgbImage.h"

class TexRect
{

    float x;
    float y;
    float w;
    float h;

    GLuint texture_id;

    int r;
    int c;
    int r1;
    int c1;
    bool Done;
    bool Exploded;

  public:
    TexRect(const char *, int, int, float, float, float, float);

	void draw();

	bool contains(float x, float y);

    bool ifDone();

    void animate();

    void explode(const char *filename, int row, int col);

    void restart(const char *filename, int row, int col);

    bool ifExplode();
};

#endif