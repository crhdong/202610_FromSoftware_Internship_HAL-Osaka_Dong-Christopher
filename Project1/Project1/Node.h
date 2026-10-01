#pragma once

#include "ScoreData.h"

struct Node
{
	ScoreData scoreData;
	Node* prev;
	Node* next;

	Node(const ScoreData& data)
		: scoreData(data), prev(nullptr), next(nullptr) { }
};