#ifndef _LOOT_H_
#define _LOOT_H_
#include "../include/position.h"
#include <iostream>

class Loot{
    int ID;
    Position position;
    int nbrFan;

public:
    Loot(int ID, Position position, int nbrFan);
    int getID();
    int getNbrFan();
    Position getPosition();
    void setNbrFan(int nbr);

};



#endif
