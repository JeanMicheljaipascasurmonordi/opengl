#ifndef _POSITION_H_
#define _POSITION_H_


typedef struct{
	int x,y,z;
}Position;


Position initPosition();
Position newPosition(int coordx, int coordy, int coordz);
bool samePosition(Position p1, Position p2);


#endif
