#ifndef _POSITION_H_
#define _POSITION_H_


typedef struct{
	float x,y,z;
}Position;


Position initPosition();
Position newPosition(float coordx, float coordy, float coordz);
bool samePosition(Position p1, Position p2);


#endif
