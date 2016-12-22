#include "../include/mur.h"
#include <iostream>

Mur::Mur(Position position, int angle, Cube3D cube){
    cube.setTranslation(10,10,10);
	//cube->setTranslation(position.x, position.y, position.z);
    //cube->setRotation( glm::vec3(0, angle, 0), 1.5f );
}

void Mur::setAngle(int angle){
	this->angle = angle;
}

int Mur::getAngle(){
	return angle;
}