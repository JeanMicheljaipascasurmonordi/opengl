#include "../include/niveau.h"
#include "../include/Cube3D.h"


using namespace std;


Niveau::Niveau(const char* file){
	ifstream fileNiveau(file);
	if(file){
		cout<<"youpi";
		fileNiveau >> fanNeeded;
		cout<<fanNeeded<<endl;
		double xDebut, yDebut, zDebut;
		fileNiveau >> xDebut;
		fileNiveau >> yDebut;
		fileNiveau >> zDebut;
		positionDebut = newPosition(xDebut, yDebut, zDebut);

		double xFin, yFin, zFin;
		fileNiveau >> xFin;
		fileNiveau >> yFin;
		fileNiveau >> zFin;
		positionFin = newPosition(xFin, yFin, zFin);

		int nbrMur;
		fileNiveau >> nbrMur;
		for (int i=0; i<nbrMur; i++){
			Position p;

			double x, y, z;
			float angle;			
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
			double x, y, z;		
			float angle;
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

			double x, y, z;
			float angle;
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
			double x, y, z;
			float angle;

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

			double x, y, z;

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

vector<Mur> Niveau::getMurs(){
	return murs;
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

bool Niveau::distanceFromObject(Position p){
	int c=0;
	for (int i=0; i<murs.size(); i++){
		if (distance(p, murs[i].getPosition()) < 1) c = 1;
	}
	for (int i=0; i<mursAngles.size(); i++){
		if (distance(p, mursAngles[i].getPosition()) < 1) c = 1;
	}
	for (int i=0; i<mursCDS.size(); i++){
		if (distance(p, mursCDS[i].getPosition()) < 1) c = 1;
	}
	return (c==0);
}


/*void Niveau::translateNiveau(double x, double y, double z){
	for (int i=0; i<murs.size(); i++){
		Position p = murs[i].getPosition();
		p.x += x;
		p.y += y;
		p.z += z;
		murs[i].setPosition(p);
	}
	for (int i=0; i<mursAngles.size(); i++){
		Position p = mursAngles[i].getPosition();
		p.x += x;
		p.y += y;
		p.z += z;
		mursAngles[i].setPosition(p);
	}
	for (int i=0; i<mursCDS.size(); i++){
		Position p = mursCDS[i].getPosition();
		p.x += x;
		p.y += y;
		p.z += z;
		mursCDS[i].setPosition(p);
	}
	for (int i=0; i<ennemis.size(); i++){
		Position p = ennemis[i].getPosition();
		p.x += x;
		p.y += y;
		p.z += z;
		ennemis[i].setPosition(p);
	}
	for (int i=0; i<loots.size(); i++){
		Position p = loots[i].getPosition();
		p.x += x;
		p.y += y;
		p.z += z;
		loots[i].setPosition(p);
	}

}*/