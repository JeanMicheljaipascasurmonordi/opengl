#ifndef _MUR_H_
#define _MUR_H_
#include "../include/position.h"
#include <iostream>

class Mur{
	Position position;
	int angle;

	public:
		Mur(Position position, int angle);
		void setAngle(int angle);
		int getAngle();

};


#endif


