#ifndef _MUR_H_
#define _MUR_H_

#include <iostream>

class Mur{
	Position position;
	int angle;

	public:
		Mur(int x, int y, int z, int angle);
		void setAngle(int angle);
		void setPosition(int x, int y, int z);
		int getAngle();

};
void drawMur();

#endif


