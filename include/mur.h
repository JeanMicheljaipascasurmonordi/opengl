#ifndef _MUR_H_
#define _MUR_H_
#include "../include/position.h"
#include "../include/cube3D.h"
#include <iostream>

class Mur{
    Position position;
    int angle;

public:
    Mur(Position position, int angle, Cube3D cube);
    void setAngle(int angle);
    int getAngle();

};


#endif


