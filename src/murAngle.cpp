#include "../include/murAngle.h"
#include <iostream>

MurAngle::MurAngle(Position position, int angle){
	this->position = position;
	this->angle = angle
}

void MurAngle::setAngle(int angle){
	this->angle = angle;
}

int MurAngle::getAngle(){
	return angle;
}