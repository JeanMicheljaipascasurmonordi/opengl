#include "../include/position.h"

#include <iostream>

Position initPosition(){
	Position p;
	p.x = 0;
	p.y = 0;
	p.z = 0;
	return p;
}

Position newPosition(float coordx, float coordy, float coordz){
	Position p;
	p.x = coordx;
	p.y = coordy;
	p.z = coordz;
	return p;
}

bool samePosition(Position p1, Position p2){
	return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
}