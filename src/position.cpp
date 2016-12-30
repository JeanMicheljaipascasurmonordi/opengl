#include "../include/position.h"

#include <iostream>
#include <math.h>

Position initPosition(){
	Position p;
	p.x = 0;
	p.y = 0;
	p.z = 0;
	return p;
}

Position newPosition(double coordx, double coordy, double coordz){
	Position p;
	p.x = coordx;
	p.y = coordy;
	p.z = coordz;
	return p;
}
double distance(Position p1, Position p2){
	return(sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.z-p1.z)*(p2.z-p1.z)));
}

bool samePosition(Position p1, Position p2){
	return (distance(p1,p2) < 0.1);
}

