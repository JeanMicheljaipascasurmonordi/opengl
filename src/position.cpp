#include "../include/position.h"

#include <iostream>

Position::Position(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
}

int Position::getX(){
	return x;
}

int Position::getX(){
	return x;
}

int Position::getX(){
	return x;
}

void setX(int x){
	this->x = x;
}

void setY(int y){
	this->y = y;
}

void setZ(int z){
	this->z = z;
}

bool Position::operator==(Position p2){
	if (x==p2.X && y==p2.Y && z==p2.z) return true;
	else return false;

}