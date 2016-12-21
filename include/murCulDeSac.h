#ifndef _MURCULDESAC_H_
#define _MURCULDESAC_H_
#include "../include/position.h"
#include <iostream>

class MurCulDeSac{
	Position position;
	int angle;

	public:
		MurCulDeSac(Position position, int angle);
		void setAngle(int angle);
		int getAngle();

};


#endif


