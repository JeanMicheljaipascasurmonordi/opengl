#ifndef _MUR_H_
#define _MUR_H_
#include "../include/position.h"
#include "../include/cube3D.h"
#include <iostream>

class Mur{
    Position position;
    float angle;

public:
    Mur(Position position, float angle);
    void setAngle(float angle);
    float getAngle();
    Position getPosition();

};


#endif


