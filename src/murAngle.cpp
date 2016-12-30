#include "../include/murAngle.h"
#include <iostream>

MurAngle::MurAngle(Position position, float angle){
	this->position = position;
	this->angle = angle;
}

void MurAngle::setAngle(float angle){
	this->angle = angle;
}

float MurAngle::getAngle(){
	return angle;
}
Position MurAngle::getPosition(){
	return position;
}

void MurAngle::setPosition(Position p){
	this->position = p;
}