#ifndef _MURANGLE_H_
#define _MURANGLE_H_
#include "../include/position.h"
#include <iostream>

class MurAngle{
	Position position;
	int angle;

	public:
		MurAngle(Position position, int angle);
		void setAngle(int angle);
		int getAngle();
		Position getPosition();
		void setPosition(Position p);

};


#endif


