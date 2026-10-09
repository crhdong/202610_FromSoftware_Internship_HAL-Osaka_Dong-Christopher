#pragma once

#include <string>

struct ScoreData
{
private:

	int score;
	std::string name;

public:

	/// コンストラクタ
	ScoreData();
	ScoreData(int i, const std::string& s);

	int GetScore() const;

	std::string GetName() const;

	void WriteScore(int newScore);

	void WriteName(const std::string& newName);
};

#include "ScoreData.inl"