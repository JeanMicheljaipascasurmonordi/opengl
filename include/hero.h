/*
#ifndef _HERO_H_
#define _HERO_H_

#include <iostream>
#include "position.h"
#include "niveau.h"
#include "ennemi.h"

class Hero{
	Position position;
	int angle;
	int pv;
	int damage;
	int nbrFan;

	public:
		Hero(Niveau niveau);
		void setAngle(int angle);
		void setPv(int pv);
		void setDamage(int damage);
		void setNbrFan(int nbrFan);
		int getAngle();
		int getPv();
		int getDamage();
		int getNbrFan();
		void attacked(Ennemi ennemi);
};

#endif*/
