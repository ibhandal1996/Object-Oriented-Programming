#include "Rectangle.h"
#include "freeglut.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void getRectangles();
void ColorChange(int, int, int, int);


int width = 800;
int height = 800;
int num = 3;
vector<Rect*> R;

int main(int argc, char** argv) 
{

	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < num; i++) 
	{
		//This gets the random rectangles from Rectangle.h
		Rect * randomRectangles = new Rect();
		R.push_back(randomRectangles);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL - Iqbal");
	glutDisplayFunc(getRectangles);

	glutMouseFunc(ColorChange);

	glutMainLoop();

	return 0;

}

void getRectangles()
{

	for (int i = 0; i < num; i++)
	{
		//Gets the colors for the differnet rectangles for the display
		glColor3f(R[i]->getRed(), R[i]->getGreen(), R[i]->getBlue());
		//Gets the sizes for the rectangles for the display
		glRectf(R[i]->getuLx(), R[i]->getuLy(), R[i]->getuLx() + R[i]->getw(), R[i]->getuLy() - R[i]->geth());
	}
	glutSwapBuffers();

}

void ColorChange(int click, int i, int x, int y)
{

	float xi, yi, xj, yj;

	xi = x;
	xj = (xi / 400 - 1.0);
	yi = y;
	yj = -(yi / 400 - 1.0);

	//Changes the colors 
	if (click == GLUT_LEFT_BUTTON && i == GLUT_DOWN)
	{
		for (int i = num - 1; i >= 0; i--)
		{
			if (R[i]->contains(xj, yj))
			{
				R[i]->color();
				break;
			}
		}
	}

}