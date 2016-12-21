#ifndef _LOOT_H_
#define _LOOT_H_

#include <iostream>

class Loot{
	int ID;
	Position position;
	int nbrFan;

	public:
		Loot(int ID, Position position, int nbrFan);
		int getID();
		int getNbrFan();

};



#endif