#pragma once

#include <string>

struct ScoreData
{
	int score;
	std::string name;

	ScoreData(int i, const std::string& s)
		: score(i), name(s) { }
};