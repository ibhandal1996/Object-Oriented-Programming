#include <iostream>
#include <deque>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


using namespace std;

int width = 800, height = 800;

void iqbal() {

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// I

	glColor3f(0.9, 0.0, 0.0);
	glRectf(-0.72 , -0.3, -0.7 , 0.3);
	glRectf(-0.93 , 0.3, -0.48, 0.28);
	glRectf(-0.93 , -0.3, -0.48, -0.28);

	// q

	glColor3f(0.0, 0.9, 0.0);
	glRectf(-0.4, -0.3, -0.42, 0.0);
	glRectf(-0.42, 0.01, -0.2, -0.01);
	glRectf(-0.2, 0.01, -0.22, -0.8);
	glRectf(-0.42, -0.3, -0.2, -0.32);


	// b

	glColor3f(0.0, 0.0, 0.9);
	glRectf(-0.15, -0.3, -0.13, 0.3);
	glRectf(-0.15, -0.3, 0.21, -0.28);
	glRectf(0.2, -0.3, 0.22, 0.0);
	glRectf(-0.15, 0.0, 0.21, -0.02);

	// a

	glColor3f(0.0, 0.9, 0.9);
	glRectf(0.26, 0.01, 0.5, -0.01);
	glRectf(0.26, -0.01, 0.28, -0.3);
	glRectf(0.48, -0.375, 0.5, 0.0);
	glRectf(0.26, -0.3, 0.48, -0.32);

	// l

	glColor3f(0.9, 0.0, 0.9);
	glRectf(0.55, 0.3, 0.57, -0.32);

	glFlush();

}

int main(int argc, char** argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	// Setup window
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL Iqbal");
	glutDisplayFunc(iqbal);

	// Start main loop
	glutMainLoop();

	return 0;

}