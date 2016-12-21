#include "../include/position.h"

#include <iostream>

Position initPosition(){
	Position p;
	p.x = 0;
	p.y = 0;
	p.z = 0;
	return p;
}

Position newPosition(int coordx, int coordy, int coordz){
	Position p;
	p.x = coordx;
	p.y = coordy;
	p.z = coordz;
	return p;
}