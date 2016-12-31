#ifndef _ENNEMI_H_
#define _ENNEMI_H_
#include "../include/position.h"
//#include "../include/hero.h"
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>

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


    //void attacked(Hero hero);

    Position getPosition();
    int getAngle();
    int getPv();
    int getDamage();
    int getFanDrop();
    void setPv(int pv);
    void setAngle(int angle);
    void setPosition(Position p);

};

#endif