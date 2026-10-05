#pragma once

#include "ScoreData.h"

struct Node
{
protected:
	ScoreData scoreData;
	Node* prev;
	Node* next;

public:
	Node(const ScoreData& data)
		: scoreData(data), prev(nullptr), next(nullptr) { }

	ScoreData& GetData()
	{
		return scoreData;
	}

	const ScoreData& GetData() const
	{
		return scoreData;
	}

	Node* GetPrev()
	{
		return prev;
	}
	Node* GetPrev() const
	{
		return prev;
	}
	Node* GetRPrev()
	{
		return next;
	}
	Node* GetRPrev() const
	{
		return next;
	}

	Node* GetNext()
	{
		return next;
	}
	Node* GetNext() const
	{
		return next;
	}
	Node* GetRNext()
	{
		return prev;
	}
	Node* GetRNext() const
	{
		return prev;
	}

	void SetPrev(Node* node)
	{
		prev = node;
	}
	void SetRPrev(Node* node)
	{
		next = node;
	}
	void SetNext(Node* node)
	{
		next = node;
	}
	void SetRNext(Node* node)
	{
		prev = node;
	}
};