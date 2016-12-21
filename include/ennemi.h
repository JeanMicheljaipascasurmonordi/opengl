/*
#ifndef _ENNEMI_H_
#define _ENNEMI_H_

#include <iostream>

#include "hero.h"

class Ennemi{
	int id;
	Hero hero;
	Position position;
	int angle;
	int pv;
	int damage;
	int fanDrop;

	public: 
		Ennemi(int id, Position position, int angle, int pv, int damage, int fanDrop);
		int getId();
		
		int get();
		//int getId();

		void attacked(Hero hero);
};

#endif*/
