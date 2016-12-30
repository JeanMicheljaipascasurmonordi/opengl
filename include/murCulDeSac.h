#ifndef _MURCULDESAC_H_
#define _MURCULDESAC_H_
#include "../include/position.h"
#include <iostream>

class MurCulDeSac{
	Position position;
	float angle;

	public:
		MurCulDeSac(Position position, float angle);
		void setAngle(float angle);
		float getAngle();
		Position getPosition();
		void setPosition(Position p);

};


#endif


