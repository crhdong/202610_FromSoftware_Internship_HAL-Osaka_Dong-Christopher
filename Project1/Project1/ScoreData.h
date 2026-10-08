#pragma once

#include <string>

struct ScoreData
{
private:

	int score;
	std::string name;

public:

	// コンストラクタ
	ScoreData()
		: score(-1), name("") {
	}
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

	// 不良なスコアを書けない
	void WriteScore(int newScore)
	{
		if (score < 0) return;
		score = newScore;
	}

	// 不良な名前を書けない
	void WriteName(const std::string& newName)
	{
		if (newName == "") return;
		name = newName;
	}
};