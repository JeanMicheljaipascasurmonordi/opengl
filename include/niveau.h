#ifndef _NIVEAU_H_
#define _NIVEAU_H_
#include "../include/mur.h"
#include "../include/murAngle.h"
#include "../include/murCulDeSac.h"
#include "../include/position.h"
#include "../include/loot.h"
#include "../include/hero.h"
#include "../include/ennemi.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Niveau{
public:
    int fanNeeded;
    vector<Mur> murs;
    vector<MurAngle> mursAngles;
    vector<MurCulDeSac> mursCDS;
    vector<Loot> loots;
    vector<Ennemi> ennemis;
    Position positionDebut;
    Position positionFin;

public:
    Niveau(const char* file);
    int getFanNeeded();
    vector<Mur> getMurs();

    void deleteLoot(int id);
    void deleteEnnemi(int id);
    bool distanceFromObject(Position p);
    void translateNiveau(double x, double y, double z);
};



#endif