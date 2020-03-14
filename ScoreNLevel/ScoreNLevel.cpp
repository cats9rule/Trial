#include "ScoreNLevel.h"

void ScoreNLevel::ScoreUp()
{
	score += 100;
}

void ScoreNLevel::LevelUp()
{
	level++;
}

void ScoreNLevel::setScore(int num)
{
	score = num;
}

int ScoreNLevel::returnScore()
{
	return score;
}

int ScoreNLevel::returnLevel()
{
	return level;
}

void ScoreNLevel::levelOne()
{
	level = 1;
}
