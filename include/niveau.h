#ifndef _NIVEAU_H_
#define _NIVEAU_H_

#include <iostream>
#include <string>
using namespace std;

class Niveau{
	int fanNeeded;
	vector<Mur> murs;
	vector<Loot> loots;
	vector<Ennemi> ennemis;
	Position positionDebut;
	Position positionFin;

	public:
		Niveau(string file);
		int getFanNeeded();
		
		void deleteLoot(int id);
		void deleteEnnemi(int id);
};

void drawLevel();

#endif