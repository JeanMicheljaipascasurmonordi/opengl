#include "mur.h"
#include <iostream>

Mur::Mur(Position position, int angle){
	this->position = position;
	this->angle = angle
}

void Mur::setAngle(int angle){
	this->angle = angle;
}

int Mur::getAngle(){
	return angle;
}