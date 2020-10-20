#include "freeglut.h"
#include <vector>
#include "TicTacToe.h"

using namespace std;

int width = 750;
int height = 750;
int n;
int screen;
int player;
int win;
vector<tictactoe> TTT;
tictactoe single(-1, 0.0, 2), mult(1, 0.0, 2);

void writeString(void*, const char s[], float, float);
void showWinner();
void makeBoxes();
void changeBox(tictactoe);
void endGame();
void Menu(int, int, int, int);


int main(int argc, char** argv) 
{
	makeBoxes();
	player = 2;
	win = '0';

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);

	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL - Iqbal");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	changeBox(single);
	changeBox(mult);

	glColor3f(0.0, 0.0, 0.0);
	writeString(GLUT_BITMAP_TIMES_ROMAN_24, "Single Player", -0.5, 0.2);
	writeString(GLUT_BITMAP_TIMES_ROMAN_24, "Two Player", 0.2, 0.2);

	glColor3f(0.0, 0.0, 0.0);
	glRectf(-0.01, 1, 0.01, -1);

	glutSwapBuffers();

	glutMouseFunc(Menu);

	glutMainLoop();

	return 0;

}

void Menu(int click, int i, int x, int y)
{
	float xi, yi, xj, yj;

	xi = x;
	xj = (xi / 400 - 1.0);
	yi = y;
	yj = -(yi / 400 - 1.0);


	if (click == GLUT_LEFT_BUTTON && i == GLUT_DOWN)
	{

		bool moved = false;

		switch (screen)
		{

		case 0:

			if (single.contains(xj, yj))
			{
				n = 1;
				screen = 1;

				glClearColor(0.0, 0.0, 0.0, 0.0);
				glClear(GL_COLOR_BUFFER_BIT);

				for (int i = 0; i < TTT.size(); i++)
				{
					changeBox(TTT[i]);
				}

				glutSwapBuffers();

				if (screen == 2)
				{
					showWinner();
				}
			}
			else if (mult.contains(xj, yj))
			{
				n = 2;
				screen = 1;

				glClearColor(0.0, 0.0, 0.0, 0.0);
				glClear(GL_COLOR_BUFFER_BIT);

				for (int i = 0; i < TTT.size(); i++)
				{
					changeBox(TTT[i]);
				}

				glutSwapBuffers();

				if (screen == 2)
				{
					showWinner();
				}
			}

			break;

		case 1:

			for (int i = 0; i < TTT.size(); i++)
			{

				if (TTT[i].contains(xj, yj) && !TTT[i].getOcc())
				{

					TTT[i].setO(player);

					if (player == 2)
						player = 1;
					else
						player = 2;

					moved = true;

				}
			}


			screen = 2;

			for (int i = 0; i < TTT.size(); i++)
			{
				if (!TTT[i].getOcc())
					screen = 1;
			}

			endGame();

			if (n == 1 && moved && screen != 2)
			{

				for (int i = 0; i < TTT.size(); i++)
				{

					if (!TTT[i].getOcc())
					{

						TTT[i].setO(player);

						if (player == 2)
							player = 1;
						else
							player = 2;

						break;

					}
				}
			}



			for (int i = 0; i < TTT.size(); i++)
			{
				if (!TTT[i].getOcc())
					screen = 1;
			}

			endGame();

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);

			for (int i = 0; i < TTT.size(); i++)
			{
				changeBox(TTT[i]);
			}

			glutSwapBuffers();

			if (screen == 2)
			{
				showWinner();
			}

			break;

		case 2:

			player = 2;
			screen = 0;
			TTT.clear();

			makeBoxes();

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);


			changeBox(single);
			changeBox(mult);
			glColor3f(0.0, 0.0, 0.0);
			writeString(GLUT_BITMAP_TIMES_ROMAN_24, "Single Player", -0.5, 0.2);
			writeString(GLUT_BITMAP_TIMES_ROMAN_24, "Two Player", 0.2, 0.2);
			glColor3f(0.0, 0.0, 0.0);
			glRectf(-0.01, 1, 0.01, -1);
			glutSwapBuffers();

			break;

		}
	}
}


void writeString(void* font, const char s[], float x, float y)
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}

void showWinner()
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (win == 2)
	{
		glColor3f(1.0, 0.0, 0.0);
		writeString(GLUT_BITMAP_TIMES_ROMAN_24, "X wins X wins X wins X wins X wins X wins", -0.6, 0.6);
		glEnd();

	}
	else if (win == 1)
	{
		glColor3f(0.0, 1.0, 1.0);
		writeString(GLUT_BITMAP_TIMES_ROMAN_24, "O wins O wins O wins O wins O wins O wins", -0.6, 0.6);
		glEnd();

	}
	else
	{
		glColor3f(1.0, 1.0, 0.0);
		writeString(GLUT_BITMAP_TIMES_ROMAN_24, "Draw Draw Draw Draw Draw Draw Draw Draw", -0.6, 0.6);
		glEnd();

	}

	win = 0;

	glutSwapBuffers();

}

void makeBoxes()
{
	float X = -1.32, Y = 0.66;
	for (int i = 0; i < 9; i++)
	{

		if (i == 3 || i == 6)
		{
			TTT.emplace_back(-0.66, Y - 0.66, 0.64);
			X = -0.66;
			Y = Y - 0.66;
		}
		else
		{
			TTT.emplace_back(X + 0.66, Y, 0.64);
			X = X + 0.66;
			Y = Y;
		}

	}
}



void changeBox(tictactoe s)
{
	float boxX1, boxX2, boxY1, boxY2;

	boxX1 = s.getX() - (0.5 * s.getL());
	boxX2 = s.getX() + (0.5 * s.getL());
	boxY1 = s.getY() - (0.5 * s.getL());
	boxY2 = s.getY() + (0.5 * s.getL());


	glColor3f(0.2, 0.0, 0.9);
	glRectf(boxX1, boxY1, boxX2, boxY2);

	if (s.getXorO() == 2)
	{
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(5.0);

		glBegin(GL_LINES);
		glVertex2f(s.getX() - 0.1, s.getY() + 0.1);
		glVertex2f(s.getX() + 0.1, s.getY() - 0.1);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(s.getX() + 0.1, s.getY() + 0.1);
		glVertex2f(s.getX() - 0.1, s.getY() - 0.1);
		glEnd();

	}
	else if (s.getXorO() == 1)
	{
		glColor3f(0.0, 0.0, 0.0);
		float twoPi = 2.0 * 3.14159265f;
		glLineWidth(5.0);
		float cos1, sin1;

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= 200; i++)
		{
			cos1 = s.getX() + (0.1 * cos(i * twoPi / 200));
			sin1 = s.getY() + (0.1 * sin(i * twoPi / 200));

			glVertex2f(cos1, sin1);
		}

		glEnd();

	}

}

void endGame()
{
	if (TTT[0].getXorO() != '\0')
	{
		if (TTT[0].getXorO() == TTT[4].getXorO())
		{
			if (TTT[0].getXorO() == TTT[8].getXorO())
			{
				screen = 2;
				win = TTT[0].getXorO();
			}
		}
	}

	if (TTT[2].getXorO() != '\0')
	{
		if (TTT[2].getXorO() == TTT[4].getXorO())
		{
			if (TTT[2].getXorO() == TTT[6].getXorO())
			{
				screen = 2;
				win = TTT[2].getXorO();
			}
		}

	}

	if (TTT[0].getXorO() != '\0')
	{
		if (TTT[0].getXorO() == TTT[1].getXorO())
		{
			if (TTT[0].getXorO() == TTT[2].getXorO())
			{
				screen = 2;
				win = TTT[0].getXorO();
			}
		}
	}

	if (TTT[3].getXorO() != '\0')
	{
		if (TTT[3].getXorO() == TTT[4].getXorO())
		{
			if (TTT[3].getXorO() == TTT[5].getXorO())
			{
				screen = 2;
				win = TTT[3].getXorO();
			}
		}
	}

	if (TTT[6].getXorO() != '\0')
	{
		if (TTT[6].getXorO() == TTT[7].getXorO())
		{
			if (TTT[6].getXorO() == TTT[8].getXorO())
			{
				screen = 2;
				win = TTT[6].getXorO();
			}
		}
	}

	if (TTT[0].getXorO() != '\0')
	{
		if (TTT[0].getXorO() == TTT[3].getXorO())
		{
			if (TTT[0].getXorO() == TTT[6].getXorO())
			{
				screen = 2;
				win = TTT[0].getXorO();
			}
		}
	}

	if (TTT[1].getXorO() != '\0')
	{
		if (TTT[1].getXorO() == TTT[4].getXorO())
		{
			if (TTT[1].getXorO() == TTT[7].getXorO())
			{
				screen = 2;
				win = TTT[1].getXorO();
			}
		}
	}

	if (TTT[2].getXorO() != '\0')
	{
		if (TTT[2].getXorO() == TTT[5].getXorO())
		{
			if (TTT[2].getXorO() == TTT[8].getXorO())
			{
				screen = 2;
				win = TTT[2].getXorO();
			}
		}
	}

}