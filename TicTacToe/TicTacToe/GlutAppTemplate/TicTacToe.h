#ifndef TICTACTOE_H
#define TICTACTOE_H

class tictactoe {

	float setX;
	float setY;
	float setL;
	int  XorO;
	bool  usedBox;

public:

	tictactoe(float x, float y, float l) {
		setX = x;
		setY = y;
		setL = l;
		XorO = 0;
		usedBox = false;
	}

	bool contains(float x, float y) 
	{
		if (x >= setX - (0.5 * setL) && x <= setX + (0.5 * setL))
		{
			if (y >= setY - (0.5 * setL) && y <= setY + (0.5 * setL))
			{
				return true;
			}
		}
		return false;
	}

	void setO(int i) 
	{
		XorO = i;
		usedBox = true;
	}

	float getX()
	{
		return setX; 
	}

	float getY()
	{
		return setY;
	}

	float getL()
	{
		return setL; 
	}

	int  getXorO()
	{
		return XorO;
	}

	bool  getOcc() 
	{
		return usedBox;
	}

};

#endif