#ifndef _MURANGLE_H_
#define _MURANGLE_H_

#include <iostream>

class MurAngle{
	Position position;
	int angle;

	public:
		MurAngle(Position position, int angle);
		void setAngle(int angle);
		int getAngle();

};


#endif


