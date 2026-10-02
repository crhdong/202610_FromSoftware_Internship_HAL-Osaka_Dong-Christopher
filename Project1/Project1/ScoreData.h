#pragma once

#include <string>

struct ScoreData
{
private:

	int score;
	std::string name;

public:

	ScoreData(int i, const std::string& s)
		: score(i), name(s) { }

	int GetScore()
	{
		return score;
	}

	int GetScore() const
	{
		return score;
	}

	std::string GetName()
	{
		return name;
	}

	std::string GetName() const
	{
		return name;
	}

	void WriteScore(int newScore)
	{
		score = newScore;
	}

	void WriteName(const std::string& newName)
	{
		name = newName;
	}
};