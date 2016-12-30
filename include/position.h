#ifndef _POSITION_H_
#define _POSITION_H_


typedef struct{
	double x,y,z;
}Position;


Position initPosition();
Position newPosition(double coordx, double coordy, double coordz);
bool samePosition(Position p1, Position p2);
double distance(Position p1, Position p2); 


#endif
