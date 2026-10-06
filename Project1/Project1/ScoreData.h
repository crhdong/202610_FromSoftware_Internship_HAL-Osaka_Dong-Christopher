#pragma once

#include <string>

struct ScoreData
{
private:

	int score;
	std::string name;

public:

	// コンストラクタ
	ScoreData(int i, const std::string& s);

	int GetScore() const;

	std::string GetName() const;

	// 不良なスコアを書けない
	void WriteScore(int newScore);

	// 不良な名前を書けない
	void WriteName(const std::string& newName);
};

#include "ScoreData.inl"