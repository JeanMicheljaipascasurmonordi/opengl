/*
#include "../include/hero.h"
#include "../include/ennemi.h"
#include "../include/niveau.h"

using namespace std;

Hero::Hero(Niveau niveau){
	this->position = niveau.positionDebut;
	this->angle = 0;
	this->pv = 10;
	this->damage = 1;
	this->nbFan=0;
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
void Hero::attacked(Ennemi ennemi){
	int perte = ennemi.getDamage();
	this->pv = pv - perte;
}*/
