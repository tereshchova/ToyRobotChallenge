#include<iostream>
#include<fstream>
#include"../ToyRobotLib//Position.hpp"
#include <string>
#include "../ToyRobotLib/ToyRobot.hpp"

using namespace std;

void displayHelp();
void displayHelp()
{
	fprintf(stdout, "\nUsage:\n\n");
	fprintf(stdout, "ToyRobotChallenge.exe \t[-input=<full filename>]\n");
	fprintf(stdout, "\nWhere:\n\n");
	fprintf(stdout, "     -input    - Input file that contains the commands\n");
	fprintf(stdout, "     -h        - Displays help\n\n");
}
int main(int argc, char** argv)
{
	int status = 0;


	try {

		if (argc > 1)
		{
			string argument1 = argv[1];
			string fileName = argument1.substr(argument1.find("=") + 1);
		//string fileName = "inputFile.txt";

		//open the file
		ifstream inputFile;
		inputFile.open(fileName, ios::in);
		if (!inputFile)
		{
			cout << ERR_INVALID_FILE << endl;
			displayHelp();
		}
		else
		{
			string line;
			Position* toyRobotPos = new Position();
			ToyRobot tr(toyRobotPos);

			while (std::getline(inputFile, line))
			{
				//read per line
				if (!tr.parser(line, *toyRobotPos))
				{
					cerr << ERR_INVALID_COMMAND << endl;
				}
			}
			delete toyRobotPos;
		}
		inputFile.close();
		}
		else
			displayHelp();

	}
	catch (...)
	{
		cerr << ERR_INVALID_FILE << endl;
		displayHelp();
		status = 1;
	}


	return status;
}