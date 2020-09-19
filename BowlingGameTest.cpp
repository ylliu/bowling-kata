#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <memory>
#include "BowlingGame.h"
/*
Briefly summarize the scoring for this form of bowling
.Each game, or “line” of bowling, includes ten turns, or “frames” for the bowler.
.In each frame, the bowler gets up to two tries to knock down all the pins.
.If in two tries, he fails to knock them all down, his score for that frame is the total number of pins knocked down in his two tries.
.If in two tries he knocks them all down, this is called a “spare” and his score for the frame is ten plus the number of pins knocked down on his next throw (in his next turn).
.If on his first try in the frame he knocks down all the pins, this is called a “strike”. His turn is over, and his score for the frame is ten plus the simple total of the pins knocked down in his next two rolls.
.If he gets a spare or strike in the last (tenth) frame, the bowler gets to throw one or two more bonus balls, respectively. These bonus throws are taken as part of the same turn. If the bonus throws knock down all the pins, the process does not repeat: the bonus throws are only used to calculate the score of the final frame.
.The game score is the total of all frame scores.
Suggested Test Cases
X X X X X X X X X X X X (12 rolls: 12 strikes) = 10 frames * 30 points = 300
9- 9- 9- 9- 9- 9- 9- 9- 9- 9- (20 rolls: 10 pairs of 9 and miss) = 10 frames * 9 points = 90
5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5 (21 rolls: 10 pairs of 5 and spare, with a final 5) = 10 frames * 15 points = 150
*/
using namespace std;
TEST_GROUP(BowlingGameTest){
	void setup(){

	}
	void teardown(){
		delete roll_scores;
	}
	BowlingGame* roll_scores;

};

TEST(BowlingGameTest, 将击球数据中的空格去掉){
	roll_scores = new BowlingGame("X X X X");
	CHECK_EQUAL("XXXX", roll_scores->Trim());
}

TEST(BowlingGameTest, 将普通字符串输入的击球情况转换为数组){
	roll_scores = new BowlingGame("21 21");
	roll_scores->Trim();
	std::vector<int> roll_pins = { 2, 1, 2, 1 };
	CHECK(roll_pins == roll_scores->TransferStringToIntArray());
}

TEST(BowlingGameTest, 当击球中出现Miss的时候把Miss改成零分){
	roll_scores = new BowlingGame("2- 2-");
	roll_scores->Trim();
	std::vector<int> roll_pins = { 2, 0, 2, 0 };
	CHECK(roll_pins == roll_scores->TransferStringToIntArray());
}

TEST(BowlingGameTest, 当击球中出现Spare的时候把Spare的分数改为10减去上一次的击球分数){
	roll_scores = new BowlingGame("2/ 2/");
	roll_scores->Trim();
	std::vector<int> roll_pins = { 2, 8, 2, 8 };
	CHECK(roll_pins == roll_scores->TransferStringToIntArray());
}

TEST(BowlingGameTest, 当击球中出现Strike的时候把Strike的分数改为10){
	roll_scores = new BowlingGame("X X");
	roll_scores->Trim();
	std::vector<int> roll_pins = { 10, 10 };
	CHECK(roll_pins == roll_scores->TransferStringToIntArray());
}


TEST(BowlingGameTest, 完整输入转换){
	roll_scores = new BowlingGame("9/ 20 00 00 00 00 00 00 00 00");
	roll_scores->Trim();
	std::vector<int> roll_pins = { 9, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	CHECK(roll_pins == roll_scores->TransferStringToIntArray());
}

TEST(BowlingGameTest, 普通击球的分数等于所有击倒的球瓶数){
	roll_scores = new BowlingGame("12 12 00 00 00 00 00 00 00 00");
	CHECK_EQUAL(6, roll_scores->Score());
}

TEST(BowlingGameTest, 当Spare击球后面是普通击球分数等于10加上下一球的分数){
	roll_scores = new BowlingGame("9/ 20 00 00 00 00 00 00 00 00");
	CHECK_EQUAL(14, roll_scores->Score());
}

TEST(BowlingGameTest, Spare击球后面是Stike的情况){
	roll_scores = new BowlingGame("9/ X 00 00 00 00 00 00 00 00");
	CHECK_EQUAL(30, roll_scores->Score());
}

TEST(BowlingGameTest, Strike击球的分数等于10加上下两球的分数){
	roll_scores = new BowlingGame("X 34 00 00 00 00 00 00 00 00");
	CHECK_EQUAL(24, roll_scores->Score());
}

TEST(BowlingGameTest, Strike击球的后面是Spare的情况){
	roll_scores = new BowlingGame("X 3/ 00 00 00 00 00 00 00 00");
	CHECK_EQUAL(30, roll_scores->Score());
}

TEST(BowlingGameTest, Stike击球后面是Strike的情况){
	roll_scores = new BowlingGame("X X X X X X X X X X X X");
	CHECK_EQUAL(300, roll_scores->Score());
}

TEST(BowlingGameTest, 当第二次Miss的时候分数是第一次击球的分数){
	roll_scores = new BowlingGame("9- 9- 9- 9- 9- 9- 9- 9- 9- 9-");
	CHECK_EQUAL(90, roll_scores->Score());
}

TEST(BowlingGameTest, 当第一次Miss的时候分数是第二次击球的分数){
	roll_scores = new BowlingGame("-9 -9 -9 -9 -9 -9 -9 -9 -9 -9");
	CHECK_EQUAL(90, roll_scores->Score());
}