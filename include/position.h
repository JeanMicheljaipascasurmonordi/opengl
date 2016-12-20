#ifndef _POSITION_H_
#define _POSITION_H_

#include <iostream>

class Position{
	int x,y,z;

	public:
		Position(int x,int y,int z);
		int getX();
		int getY();
		int getZ();
		void setX();
		void setY();
		void setZ();
};

#endif