#include "../include/murCulDeSac.h"
#include <iostream>

MurCulDeSac::MurCulDeSac(Position position, float angle){
	this->position = position;
	this->angle = angle;
}

void MurCulDeSac::setAngle(float angle){
	this->angle = angle;
}

float MurCulDeSac::getAngle(){
	return angle;
}
Position MurCulDeSac::getPosition(){
	return position;
}