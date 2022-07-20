// ToyRobotLib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include <string>
#include "Position.hpp"
#include <iostream>
#include "ToyRobot.hpp"

const int MAXTABLEUNITS = 5;

using namespace std;



ToyRobot::ToyRobot(Position* rPosition) : robotPosition(rPosition)
{ }

Position ToyRobot::place(Position& rPosition)
{
	Position toyRobotPos;
	if (rPosition.IsValidDirection(rPosition.getFacingDirection()) && rPosition.IsValidXY(rPosition.getXPosition(), rPosition.getYPosition()))
	{
		this->resetAll(toyRobotPos);
		toyRobotPos.setXPosition(rPosition.getXPosition());
		toyRobotPos.setYPosition(rPosition.getYPosition());
		toyRobotPos.setFacingDirection(rPosition.getFacingDirection());
	}
	else
	{
		cout << ERR_INVALID_X_Y << endl;
	}
	return toyRobotPos;
}

Position ToyRobot::left(Position& rPosition)
{
	Position toyRobotPos;
	if (rPosition.IsValidDirection(rPosition.getFacingDirection()) && rPosition.IsValidXY(rPosition.getXPosition(), rPosition.getYPosition()))
	{
		toyRobotPos.setXPosition(rPosition.getXPosition());
		toyRobotPos.setYPosition(rPosition.getYPosition());

		if (rPosition.getFacingDirection().compare("NORTH") == 0)
			toyRobotPos.setFacingDirection("WEST");
		else if (rPosition.getFacingDirection().compare("WEST") == 0)
			toyRobotPos.setFacingDirection("SOUTH");
		else if (rPosition.getFacingDirection().compare("SOUTH") == 0)
			toyRobotPos.setFacingDirection("EAST");
		else if (rPosition.getFacingDirection().compare("EAST") == 0)
			toyRobotPos.setFacingDirection("NORTH");
	}
	else
	{
		cout << ERR_INVALID_X_Y << endl;
	}
	return toyRobotPos;
}

Position ToyRobot::right(Position& rPosition)
{
	Position toyRobotPos;
	if (rPosition.IsValidDirection(rPosition.getFacingDirection()) && rPosition.IsValidXY(rPosition.getXPosition(), rPosition.getYPosition()))
	{
		toyRobotPos.setXPosition(rPosition.getXPosition());
		toyRobotPos.setYPosition(rPosition.getYPosition());

		if (rPosition.getFacingDirection().compare("NORTH") == 0)
			toyRobotPos.setFacingDirection("EAST");
		else if (rPosition.getFacingDirection().compare("WEST") == 0)
			toyRobotPos.setFacingDirection("NORTH");
		else if (rPosition.getFacingDirection().compare("SOUTH") == 0)
			toyRobotPos.setFacingDirection("WEST");
		else if (rPosition.getFacingDirection().compare("EAST") == 0)
			toyRobotPos.setFacingDirection("SOUTH");
	}
	else
	{
		cout << ERR_INVALID_X_Y << endl;
	}
	return toyRobotPos;
}

Position ToyRobot::move(Position& rPosition)
{
	Position toyRobotPos;
	if (rPosition.IsValidDirection(rPosition.getFacingDirection()) && rPosition.IsValidXY(rPosition.getXPosition(), rPosition.getYPosition()))
	{
		toyRobotPos.setFacingDirection(rPosition.getFacingDirection());
		toyRobotPos.setXPosition(rPosition.getXPosition());
		toyRobotPos.setYPosition(rPosition.getYPosition());

		if (rPosition.getFacingDirection().compare("NORTH") == 0)
			toyRobotPos.setYPosition(rPosition.getYPosition() + 1);
		else if (rPosition.getFacingDirection().compare("WEST") == 0)
			toyRobotPos.setXPosition(rPosition.getXPosition() - 1);
		else if (rPosition.getFacingDirection().compare("SOUTH") == 0)
			toyRobotPos.setYPosition(rPosition.getYPosition() - 1);
		else if (rPosition.getFacingDirection().compare("EAST") == 0)
			toyRobotPos.setXPosition(rPosition.getXPosition() + 1);
	}
	else
	{
		cout << ERR_INVALID_X_Y << endl;
	}
	return toyRobotPos;
}

Position ToyRobot::resetAll(Position& robotPosition)
{
	robotPosition.setXPosition(0);
	robotPosition.setYPosition(0);
	robotPosition.setFacingDirection("");
	robotPosition.setIsPlaced(false);
	return robotPosition;
}

Position ToyRobot::printReport(Position& robotPosition)
{
	cout << "Output: " << robotPosition.getXPosition() << "," << robotPosition.getYPosition() << "," << robotPosition.getFacingDirection() << endl;
	return robotPosition;
}

bool ToyRobot::parser(string line, Position& rPosition)
{
	bool OKStatus = true;
	if (!line.empty())
	{
		string firstCommand = line.substr(0, line.find(" "));
		int countValid = std::count(line.begin(), line.end(),',');
		try
		{
			//cout << "\nfirstCommand: " << firstCommand<< "|";
			if (firstCommand.compare("PLACE") == 0 && (countValid ==2))
			{
				this->resetAll(rPosition);
				string toSplit = line.substr(line.find(" ") + 1);
				string lineX = toSplit.substr(toSplit.find(",") - 1, 1);
				string lineY = toSplit.substr(toSplit.find(",") + 1, 1);
				string lineDirection = toSplit.substr(toSplit.find_last_of(",") + 1);

				rPosition.setXPosition(stoi(lineX));
				rPosition.setYPosition(stoi(lineY));
				rPosition.setFacingDirection(lineDirection);
				if (rPosition.IsValidDirection(rPosition.getFacingDirection()) && rPosition.IsValidXY(rPosition.getXPosition(), rPosition.getYPosition()))
				{
					rPosition = this->place(rPosition);
					rPosition.setIsPlaced(true);
				}
				else
				{
					rPosition.setIsPlaced(false);
					return OKStatus = false;
				}
			}
			else
			{
				if (rPosition.getIsPlaced())
				{
					if (firstCommand.compare("LEFT") == 0)
						rPosition = this->left(rPosition);
					else if (firstCommand.compare("RIGHT") == 0)
						rPosition = this->right(rPosition);
					else if (firstCommand.compare("MOVE") == 0)
						rPosition = this->move(rPosition);
					else if (firstCommand.compare("REPORT") == 0)
					{
						if (rPosition.getFacingDirection().compare("") != 0)
						{
							rPosition = this->printReport(rPosition);
							rPosition.setIsPlaced(false);
						}
					}
					else {
						rPosition.setIsPlaced(false);
						return OKStatus = false;
					}
				}
				else {
					rPosition.setIsPlaced(false);
					return OKStatus = false;
				}
			}

		}
		catch (...) {
			rPosition.setIsPlaced(false);
			return OKStatus = false;
		}
	}
	else
		OKStatus = false;

	return OKStatus;
}
