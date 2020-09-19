#pragma once
#include <string>
#include <vector>
class BowlingGame
{
public:
	BowlingGame(std::string rolls)
		:rolls_(rolls)
	{

	}

	~BowlingGame()
	{
	}
public:
	std::string Trim();
	std::vector<int> TransferStringToIntArray();
	int Score();
protected:

private:
	bool IsSpare(int roll_index);
	bool IsStrike(int roll_index);
	int SpareBonus(int roll_index);
	int StikeBonus(int roll_index);
	int SumOfBallsInFrame(int roll_index);

	std::string rolls_;
	std::vector<int> roll_pins_;
	const int TOTAL_FRAMES = 10;
	const int TOTAL_PINS = 10;
};
