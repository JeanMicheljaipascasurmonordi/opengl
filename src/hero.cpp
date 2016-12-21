#include "../include/hero.h"


using namespace std;

Hero::Hero(){
    this->position = newPosition(0,0,0);
    this->angle = 0;
    this->pv = 10;
    this->damage = 1;
    this->nbrFan=0;
}


void Hero::setAngle(int angle){
    this->angle = angle;
}
void Hero::setPv(int pv){
    this->pv = pv;
}
void Hero::setDamage(int damage){
    this->damage = damage;
}
void Hero::setNbrFan(int nbFan){
    this->nbrFan = nbrFan;
}


int Hero::getAngle(){
    return(angle);
}
int Hero::getPv(){
    return pv;
}
int Hero::getDamage(){
    return damage;
}
int Hero::getNbrFan(){
    return nbrFan;
}

/*void Hero::attacked(Ennemi ennemi){
	this->pv = pv - ennemi.getDamage();
}*/
