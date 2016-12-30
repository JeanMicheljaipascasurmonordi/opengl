#ifndef _MURANGLE_H_
#define _MURANGLE_H_
#include "../include/position.h"
#include <iostream>

class MurAngle{
	Position position;
	float angle;

	public:
		MurAngle(Position position, float angle);
		void setAngle(float angle);
		float getAngle();
		Position getPosition();

};


#endif


