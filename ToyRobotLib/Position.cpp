#include "pch.h"
#include "Position.hpp"

using namespace std;
const int MAXTABLEUNITS = 5;

int Position::getXPosition()
{
	return this->x;
}

int Position::getYPosition()
{
	return this->y;
}

string Position::getFacingDirection()
{
	return this->facingDirection;
}

void Position::setXPosition(int posX)
{
	this->x = posX;
}

void Position::setYPosition(int posY)
{
	this->y = posY;
}

void Position::setIsPlaced(bool placeValue)
{
	this->isPlaced = placeValue;
}

bool Position::getIsPlaced()
{
	return this->isPlaced;
}

void Position::setFacingDirection(string currentDirection)
{
	this->facingDirection = currentDirection;
}

bool Position::IsValidXY(int posX, int posY)
{
	return ((posX >= MAXTABLEUNITS || posX < 0) || (posY >= MAXTABLEUNITS || posY < 0)) ? false : true;
}

bool Position::IsValidDirection(std::string currentDirection)
{
    return (currentDirection.compare("NORTH") == 0 || currentDirection.compare("EAST") == 0 || currentDirection.compare("WEST") == 0 || currentDirection.compare("SOUTH") == 0);
}
