#include "../include/ennemi.h"

Ennemi::Ennemi(int id, Position position, int angle, int pv, int damage, int fanDrop){
	this->id = id;
	this->position = position;
	this->angle = angle;
	this->pv = pv;
	this->damage = damage;
	this->fanDrop = fanDrop;
}


int Ennemi::getId(){
	return id;
}

int Ennemi::getPv(){
	return pv;
}
int Ennemi::getAngle(){
	return angle;
}
int Ennemi::getFanDrop(){
	return fanDrop;
}

Position Ennemi::getPosition(){
	return position;
}

void Ennemi::setAngle(int angle){
	this->angle = angle;
}

void Ennemi::setPv(int pv){
	this->pv = pv;
}

void Ennemi::setPosition(Position p){
	this->position = p;
}

void Ennemi::setNbrFan(int nbr){
	this->fanDrop = nbr;
}