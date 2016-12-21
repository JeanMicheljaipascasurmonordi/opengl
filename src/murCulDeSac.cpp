#include "../include/murCulDeSac.h"
#include <iostream>

MurCulDeSac::MurCulDeSac(Position position, int angle){
	this->position = position;
	this->angle = angle
}

void MurCulDeSac::setAngle(int angle){
	this->angle = angle;
}

int MurCulDeSac::getAngle(){
	return angle;
}