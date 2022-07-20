#include "pch.h"
#include "../ToyRobotLib//Position.hpp"
#include "../ToyRobotLib/ToyRobot.hpp"
#include <gtest/gtest.h>


#pragma region TEST Valid and Invalid Facing Directions
class PositionFixture :public testing::TestWithParam<std::tuple<string, bool>>
{
	
public:
protected: 
	Position mPosition;
};

TEST_P(PositionFixture, TestValidDirection)
{
	std::tuple<string, bool> tuple = GetParam();

	string param = std::get<0>(tuple);
	bool expectedValue = std::get<1>(tuple);

	std::cout << "param = " << param << " expected value = " << expectedValue << '\n';


	bool isInside = mPosition.IsValidDirection(param);
	ASSERT_EQ(expectedValue, isInside);
}

INSTANTIATE_TEST_CASE_P(TestValidDirection, PositionFixture, testing::Values(
	make_tuple("NORTH", true),
	make_tuple("EAST", true),
	make_tuple("WEST", true),
	make_tuple("SOUTH", true),
	make_tuple("nORth", false),
	make_tuple("East", false),
	make_tuple("wESt", false),
	make_tuple("SOTH", false),
	make_tuple("INVALID", false),
	make_tuple("", false)
));

#pragma endregion

#pragma region TEST Getter and Setter Directions
TEST_F(PositionFixture, TestGetterSetterDirection)
{
	string param = "NORTH";

	mPosition.setFacingDirection(param);
	ASSERT_EQ(mPosition.getFacingDirection(), param);

	mPosition.setFacingDirection(param);
	ASSERT_NE(mPosition.getFacingDirection(), "north");

	mPosition.setFacingDirection(param);
	ASSERT_NE(mPosition.getFacingDirection(), "");

	mPosition.setFacingDirection(param);
	ASSERT_NE(mPosition.getFacingDirection(), "NORTH ");

}

#pragma endregion

#pragma region TEST Valid Coordinates-Position
class PositionFixture2 :public testing::TestWithParam<tuple<int, bool>>
{
public:
protected:
	Position mPosition;
};


TEST_P(PositionFixture2, TestPositionInRange)
{
	tuple<int, bool> tuple = GetParam();
	int param1 = get<0>(tuple);
	int param2 = get<0>(tuple);
	bool expectedValue = get<1>(tuple);
	bool isValidPosition = mPosition.IsValidXY(param1, param2);//mPosition.isValidPosition(param1, param2);
	ASSERT_EQ(expectedValue, isValidPosition);
}


INSTANTIATE_TEST_CASE_P(TestValidPosition, PositionFixture2, testing::Values(
	make_tuple(-5, false),
	make_tuple(-1, false),
	make_tuple(4, true),
	make_tuple(0,true),
	make_tuple(1, true),
	make_tuple(2, true),
	make_tuple(3, true),
	make_tuple(5, false),
	make_tuple(6, false)
));

#pragma endregion

#pragma region TEST Getter and Setter Coordinates
TEST_F(PositionFixture2, TestGetterSetterXY)
{	
	int param1 = 0;
	int param2 = 0;

	mPosition.setXPosition(param1);
	ASSERT_EQ(mPosition.getXPosition(), param1);

	mPosition.setXPosition(param1);
	ASSERT_NE(mPosition.getXPosition(), 1);

	mPosition.setYPosition(param2);
	ASSERT_EQ(mPosition.getYPosition(), param2);

	mPosition.setYPosition(param2);
	ASSERT_NE(mPosition.getYPosition(), 2);
}

#pragma endregion

#pragma region TEST Getter and Setter IsPlaced
TEST_F(PositionFixture2, TestGetterSetterIsPlaced)
{
	bool param1 = true;
	bool param2 = false;

	mPosition.setIsPlaced(param1);
	ASSERT_TRUE(mPosition.getIsPlaced());

	mPosition.setIsPlaced(param2);
	ASSERT_FALSE(mPosition.getIsPlaced());
}
#pragma endregion

struct ToyRobotFixture :public::testing::Test {
	ToyRobotFixture() :toyRobot_(&pos) {}
	void SetUp()
	{
	}
	void TearDown()
	{
	}
	Position pos;
	ToyRobot toyRobot_;
};

#pragma region TEST Reset Command
TEST_F(ToyRobotFixture, TestResetCommand)
{
	Position& rPosition(pos);
	Position expectedPos;
	expectedPos = toyRobot_.resetAll(rPosition);
	EXPECT_EQ(0, expectedPos.getXPosition());
	EXPECT_EQ(0, expectedPos.getYPosition());
	EXPECT_EQ("", expectedPos.getFacingDirection());
}

#pragma endregion

#pragma region TEST Print Command
TEST_F(ToyRobotFixture, TestPrintCommand)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(4);
	rPosition.setYPosition(4);
	rPosition.setFacingDirection("NORTH");
	expectedPos = toyRobot_.printReport(rPosition);
	EXPECT_EQ(4, expectedPos.getXPosition());
	EXPECT_EQ(4, expectedPos.getYPosition());
	EXPECT_EQ("NORTH", expectedPos.getFacingDirection());
}

#pragma endregion

#pragma region TEST MOVE Command
TEST_F(ToyRobotFixture, TestValidMoveUpwardCommand)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(0);
	rPosition.setYPosition(0);
	rPosition.setFacingDirection("NORTH");
	expectedPos = toyRobot_.move(rPosition);
	EXPECT_EQ(0, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());
	EXPECT_EQ("NORTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestInvalidMoveUpwardCommand)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(0);
	rPosition.setYPosition(0);
	rPosition.setFacingDirection("NORTH");
	
	expectedPos = toyRobot_.move(rPosition);
	EXPECT_EQ(0, expectedPos.getXPosition());
	EXPECT_NE(0, expectedPos.getYPosition());
	EXPECT_EQ("NORTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestValidMoveDownwardCommand)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("SOUTH");
	expectedPos = toyRobot_.move(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(0, expectedPos.getYPosition());
	EXPECT_EQ("SOUTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestInvalidMoveDownwardCommand)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("SOUTH");

	expectedPos = toyRobot_.move(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_NE(1, expectedPos.getYPosition());
	EXPECT_EQ("SOUTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestValidMovSideward1Command)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("EAST");
	expectedPos = toyRobot_.move(rPosition);
	EXPECT_EQ(2, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());
	EXPECT_EQ("EAST", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestValidMovSideward2Command)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("WEST");

	expectedPos = toyRobot_.move(rPosition);
	EXPECT_EQ(0, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());
	EXPECT_EQ("WEST", expectedPos.getFacingDirection());
}

#pragma endregion

#pragma region TEST LEFT Command
TEST_F(ToyRobotFixture, TestLeftCommandFacingWest)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("WEST");

	expectedPos = toyRobot_.left(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("SOUTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestLeftCommandFacingNorth)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("NORTH");

	expectedPos = toyRobot_.left(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("WEST", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestLeftCommandFacingEast)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("EAST");

	expectedPos = toyRobot_.left(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("NORTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestLeftCommandFacingSouth)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("SOUTH");

	expectedPos = toyRobot_.left(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("EAST", expectedPos.getFacingDirection());
}
#pragma endregion

#pragma region TEST RIGHT Command
TEST_F(ToyRobotFixture, TestRightCommandFacingWest)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("WEST");

	expectedPos = toyRobot_.right(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("NORTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestRightCommandFacingNorth)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("NORTH");

	expectedPos = toyRobot_.right(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("EAST", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestRightCommandFacingEast)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("EAST");

	expectedPos = toyRobot_.right(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("SOUTH", expectedPos.getFacingDirection());
}
TEST_F(ToyRobotFixture, TestRightCommandFacingSouth)
{
	Position& rPosition(pos);
	Position expectedPos;

	rPosition.setXPosition(1);
	rPosition.setYPosition(1);
	rPosition.setFacingDirection("SOUTH");

	expectedPos = toyRobot_.right(rPosition);
	EXPECT_EQ(1, expectedPos.getXPosition());
	EXPECT_EQ(1, expectedPos.getYPosition());;
	EXPECT_EQ("WEST", expectedPos.getFacingDirection());
}
#pragma endregion

#pragma region TEST Parser
TEST_F(ToyRobotFixture, TestParserInvalid)
{
	Position& rPosition(pos);
	//bool parser(string command, Position & rPosition);
	string invalidCommand1 = "test command";
	string invalidCommand2 = "MOVE ";
	string invalidCommand3 = "PLACE 1, 1, NORTH ";
	string invalidCommand4 = "report";
	string invalidCommand5 = "PLACE 1,1,NORTH,TEST";
	string invalidCommand6 = "PLACE 1,1,";
	string invalidCommand7 = "PLACE 1,1";
	string invalidCommand8 = " ";
	string invalidCommand9 = "";

	auto invalidCommands = vector<string>{ invalidCommand1, invalidCommand2, invalidCommand3, invalidCommand4, invalidCommand5, invalidCommand6, invalidCommand6, invalidCommand8, invalidCommand9};
	for (auto vals : invalidCommands)
		EXPECT_FALSE(toyRobot_.parser(vals, rPosition));
}
TEST_F(ToyRobotFixture, TestParserValid)
{
	Position& rPosition(pos);

	string validCommand1 = "PLACE 1,1,NORTH";
	string validCommand2 = "MOVE";
	string validCommand3 = "LEFT";
	string validCommand4 = "RIGHT";
	string validCommand5 = "REPORT";
	string validCommand6 = "PLACE 4,4,EAST";
	auto validCommands = vector<string>{ validCommand1, validCommand2, validCommand3, validCommand4, validCommand5 };
	for (auto vals : validCommands)
		EXPECT_TRUE(toyRobot_.parser(vals, rPosition));
}
#pragma endregion
