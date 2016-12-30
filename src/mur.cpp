#include "../include/mur.h"
#include <iostream>

Mur::Mur(Position position, float angle){
   	this->position = position;
   	this->angle = angle;
}

void Mur::setAngle(float angle){
	this->angle = angle;
}

float Mur::getAngle(){
	return angle;
}

Position Mur::getPosition(){
	return position;
}