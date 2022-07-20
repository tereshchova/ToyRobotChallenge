#pragma once
#include "pch.h"
#include "framework.h"
#include <string>
#include "Position.hpp"
#include <iostream>

#define ERR_INVALID_X_Y   "Invalid values of X and Y"
#define ERR_INVALID_FILE  "Invalid Input file"
#define ERR_INVALID_COMMAND "Invalid Command"

class ToyRobot
{
private:
	Position* robotPosition;

public:
	//ToyRobot(int posX = 0, int posY = 0, string currentDirection = "");
	ToyRobot(Position* rPosition);
	~ToyRobot() = default;


	Position place(Position& rPosition);
	Position left(Position& robotPosition);
	Position right(Position& robotPosition);
	Position move(Position& robotPosition);
	Position resetAll(Position& robotPosition);
	Position printReport(Position& robotPosition);
	bool parser(string command, Position& rPosition);
};