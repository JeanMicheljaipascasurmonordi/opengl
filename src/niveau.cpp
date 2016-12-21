#include "../include/niveau.h"


using namespace std;

Niveau::Niveau(string file){
	ifstream fileNiveau(file);
	if(file){
		fileNiveau >> fanNeeded;
		int xDebut, yDebut, zDebut;
		fileNiveau >> xDebut;
		fileNiveau >> yDebut;
		fileNiveau >> zDebut;
		positionDebut = Position(xDebut, yDebut, zDebut);

		int xFin, yFin, zFin;
		fileNiveau >> xFin;
		fileNiveau >> yFin;
		fileNiveau >> zFin;
		positionFin = Position(xFin, yFin, zFin);

		int nbrMur;
		fileNiveau >> nbrMur;
		for (int i=0; i<nbrMur; i++){
			Mur m;
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = Position(x,y,z);
			m = Mur(p, angle);
			murs.push_back(m);
		}

		int nbrMurAngle;
		fileNiveau >> nbrMurAngle;
		for (int i=0; i<nbrMurAngle; i++){
			MurAngle m;
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = Position(x,y,z);
			m = MurAngle(p, angle);
			mursAngles.push_back(m);
		}

		int nbrMurCDS;
		fileNiveau >> nbrMurCDS;
		for (int i=0; i<nbrMurCDS; i++){
			MurCulDeSac m;
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = Position(x,y,z);
			m = MurCulDeSac(p, angle);
			mursCDS.push_back(p);
		}

		int nbrEnnemi;
		fileNiveau >> nbrEnnemi;
		for (int i=0; i<nbrEnnemi; i++){
			Ennemi e;
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = Position(x,y,z);
			e = Ennemi(i, p, angle, 5, 1, 10);
			ennemis.push_back(e);
		}

		int nbrLoot;
		fileNiveau >> nbrLoot;
		for (int i=0; i<nbrLoot; i++){
			Loot l;
			Position p;
			int x, y, z;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			p = Position(x,y,z);
			l = Loot(i, p, 5);
			loots.push_back(l);
		}

	}
}


int Niveau::getFanNeeded(){
	return fanNeeded;
}

void Niveau::deleteLoot(int id){
	int size = loots.size();
	int c=0;
	while (loots.ID != id) c++;
	loots[c]=loots[size-1];
	loots.pop_back();
}


void Niveau::deleteEnnemi(int id){
	int size = ennemis.size();
	int c=0;
	while (ennemis.ID != id) c++;
	ennemis[c]=ennemis[size-1];
	ennemis.pop_back();
}

