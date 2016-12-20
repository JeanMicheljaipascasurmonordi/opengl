#ifndef _HERO_H_
#define _HERO_H_

#include <iostream>

class Hero{
	int x,y,z;
	int angle;
	int pv;
	int damage;
	int nbrFan;

	public:
		Hero(Niveau Niveau);
		void setAngle(int angle);
		void setPosition(int x, int y, int z);
		void setPv(int pv);
		void setDamage(int damage);
		void setNbrFan(int nbrFan);
		int getX();
		int getY();
		int getZ();
		int getAngle();
		int getPv();
		int getDamage();
		int getNbrFan();
};

#endif