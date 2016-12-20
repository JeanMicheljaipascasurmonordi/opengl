#ifndef _LOOT_H_
#define _LOOT_H_

#include <iostream>

class Loot{
	int ID;
	Position Position;
	int nbrFan;

	public:
		Loot(int ID, Position Position, int nbrFan);
		int getID();
		int nbrFan();

};

void drawLoot();

#endif