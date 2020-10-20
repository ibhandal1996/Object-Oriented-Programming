#pragma once
#include <cstdlib>

class Rect 
{

	float red;
	float green;
	float blue;
	float uLx;
	float uLy;
	float w;
	float h;

public:

	float getRed()
	{
		return red;
	}

	float getGreen()
	{
		return green;
	}

	float getBlue()
	{
		return blue;
	}

	float getuLx()
	{
		return uLx;
	}

	float getuLy()
	{
		return uLy;
	}

	float getw()
	{
		return w;
	}

	float geth()
	{
		return h;
	}

	//needed for the color change when the rectangles are clicked
	void color() 
	{
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

	}

	//makes the random rectangles
	Rect() 
	{
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;
		uLx = ((.8 - (-.8)) * ((float)rand() / RAND_MAX)) + (-.8);
		w = ((.1 - (1 - uLx)) * ((float)rand() / RAND_MAX)) + (1 - uLx);
		uLy = ((.8 - (-.8)) * ((float)rand() / RAND_MAX)) + (-.8);
		h = ((.1 - (1 - uLy)) * ((float)rand() / RAND_MAX)) + (1 - uLy);

	}

	bool contains(float x, float y) 
	{
		if (x >= uLx && x <= uLx + w)
			if (y <= uLy && y >= uLy - h)
				return true;

		return false;

	}
};