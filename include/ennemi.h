#ifndef _ENNEMI_H_
#define _ENNEMI_H_
#include "../include/position.h"
#include "../include/hero.h"
#include <iostream>

class Ennemi{
    int id;
    Position position;
    int angle;
    int pv;
    int damage;
    int fanDrop;

public:
    Ennemi(int id, Position position, int angle, int pv, int damage, int fanDrop);
    int getId();

    int getAngle();
    int getPv();
    int getDamage();
    int getFanDrop();
    void setPv(int pv);
    void setAngle(int angle);

    void attacked(Hero hero);
};

#endif
