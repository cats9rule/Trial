#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <sstream>
#include <iostream>
using namespace sf;

class ScoreNLevel
{
private:
	int score = 0;
	int level = 1;
public:
	void ScoreUp();
	void LevelUp();
	void setScore(int num);
	int returnScore();
	int returnLevel();
	void levelOne();
};

