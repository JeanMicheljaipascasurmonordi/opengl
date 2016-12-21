#include "../include/niveau.h"


using namespace std;

Niveau::Niveau(char* file){
	ifstream fileNiveau(file);
	if(file){
		fileNiveau >> fanNeeded;
		int xDebut, yDebut, zDebut;
		fileNiveau >> xDebut;
		fileNiveau >> yDebut;
		fileNiveau >> zDebut;
		positionDebut = newPosition(xDebut, yDebut, zDebut);

		int xFin, yFin, zFin;
		fileNiveau >> xFin;
		fileNiveau >> yFin;
		fileNiveau >> zFin;
		positionFin = newPosition(xFin, yFin, zFin);

		int nbrMur;
		fileNiveau >> nbrMur;
		for (int i=0; i<nbrMur; i++){
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = newPosition(x,y,z);
			Mur m = Mur(p, angle);
			murs.push_back(m);
		}

		int nbrMurAngle;
		fileNiveau >> nbrMurAngle;
		for (int i=0; i<nbrMurAngle; i++){
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = newPosition(x,y,z);
			MurAngle m = MurAngle(p, angle);
			mursAngles.push_back(m);
		}

		int nbrMurCDS;
		fileNiveau >> nbrMurCDS;
		for (int i=0; i<nbrMurCDS; i++){
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = newPosition(x,y,z);
			MurCulDeSac m = MurCulDeSac(p, angle);
			mursCDS.push_back(m);
		}

		int nbrEnnemi;
		fileNiveau >> nbrEnnemi;
		for (int i=0; i<nbrEnnemi; i++){
			Position p;
			int x, y, z, angle;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			fileNiveau >> angle;
			p = newPosition(x,y,z);
			Ennemi e = Ennemi(i, p, angle, 5, 1, 10);
			ennemis.push_back(e);
		}

		int nbrLoot;
		fileNiveau >> nbrLoot;
		for (int i=0; i<nbrLoot; i++){
			Position p;
			int x, y, z;
			fileNiveau >> x;
			fileNiveau >> y;
			fileNiveau >> z;
			p = newPosition(x,y,z);
			Loot l = Loot(i, p, 5);
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
	while (loots[c].getID() != id) c++;
	loots[c]=loots[size-1];
	loots.pop_back();
}


void Niveau::deleteEnnemi(int id){
	int size = ennemis.size();
	int c=0;
	while (ennemis[c].getId() != id) c++;
	ennemis[c]=ennemis[size-1];
	ennemis.pop_back();
}

