#pragma once

#include "ScoreData.h"

struct Node
{
	ScoreData scoreData;
	Node* prev;
	Node* next;

public:
	Node(const ScoreData& data)
		: scoreData(data), prev(nullptr), next(nullptr) { }

	int GetScore()
	{
		return scoreData.score;
	}

	int GetScore() const
	{
		return scoreData.score;
	}

	std::string GetName()
	{
		return scoreData.name;
	}

	std::string GetName() const
	{
		return scoreData.name;
	}
};