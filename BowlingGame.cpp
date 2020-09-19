#include "BowlingGame.h"
#include<algorithm>
using namespace std;

std::string BowlingGame::Trim()
{
	int index = 0;
	if (!rolls_.empty())
	{
		while ((index = rolls_.find(' ', index)) != string::npos)
		{
			rolls_.erase(index, 1);
		}
	}
	return rolls_;
}

int BowlingGame::Score()
{
	// 9- 9/ 9- X X -/ 12 00 00 00   
	Trim();  //ȥ���ո� 9-9/9-XX-/12000000 
	TransferStringToIntArray(); //ת�������ӱ����������� 9,0,9,1,9,0,10,10,0,10,1,2,0,0,0,0,0,0
	int total_score = 0;
	int roll_index = 0;
	for (int i = 0; i < TOTAL_FRAMES; i++){

		if (IsStrike(roll_index)){
			total_score += TOTAL_PINS + StikeBonus(roll_index);
			roll_index++;
			continue;
		}

		if (IsSpare(roll_index)){
			total_score += TOTAL_PINS + SpareBonus(roll_index);
			roll_index += 2;
			continue;
		}

		total_score += SumOfBallsInFrame(roll_index);
		roll_index += 2;
	}
	return total_score;
}

bool BowlingGame::IsSpare(int roll_index)
{
	return roll_pins_[roll_index] + roll_pins_[roll_index + 1] == TOTAL_PINS;
}

int BowlingGame::SpareBonus(int roll_index)
{
	return roll_pins_[roll_index + 2];
	//����ط����״�һ��ʼд����+1��ʵ��Ӧ����+2 ����466 
	//��4��ʼ�ж��ǲ���4+6����10������ô������6 ������+2
}

int BowlingGame::SumOfBallsInFrame(int roll_index)
{
	return roll_pins_[roll_index] + roll_pins_[roll_index + 1];
}

bool BowlingGame::IsStrike(int roll_index)
{
	return roll_pins_[roll_index] == TOTAL_PINS;
}

int BowlingGame::StikeBonus(int roll_index)
{
	return roll_pins_[roll_index + 1] + roll_pins_[roll_index + 2];
}
std::vector<int> BowlingGame::TransferStringToIntArray()
{
	for (int i = 0; i < rolls_.size(); i++)
	{
		char roll = rolls_[i];

		if (roll == 'X'){
			roll_pins_.push_back(TOTAL_PINS);
			continue;
		}

		if (roll == '/'){
			char last_roll = rolls_[i - 1];
			roll_pins_.push_back(TOTAL_PINS - atoi(&last_roll));
			continue;
		}
		roll_pins_.push_back(atoi(&roll));
	}
	return roll_pins_;
}


