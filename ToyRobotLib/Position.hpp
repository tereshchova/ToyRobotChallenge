#pragma once
#include<string>

using namespace std;

class Position
{
private:
	int x;
	int y;
	string facingDirection;
	bool isPlaced;
public: 
	Position() = default;

	int getXPosition();
	int getYPosition() ;
	string getFacingDirection();
	void setXPosition(int posX);
	void setYPosition(int posY);
	void setIsPlaced(bool placeValue);
	bool getIsPlaced();
	void setFacingDirection(string currentDirection);
	bool IsValidXY(int posX, int posY);
	bool IsValidDirection(std::string currentDirection);
};
