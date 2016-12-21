#include "../include/loot.h"

#include <iostream>

Loot::Loot(int ID, Position position, int nbrFan){
	this->ID = ID;
	this->position = position;
	this->nbrFan;
}

int Loot::getID(){
	return ID;
}

int Loot::getNbrFan(){
	return nbrFan;
}

