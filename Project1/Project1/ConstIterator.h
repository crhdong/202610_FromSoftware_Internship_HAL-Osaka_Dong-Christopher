#pragma once

#include "Node.h"


// コンストイテレータ
class ConstIterator
{
protected:
	const Node* current;

public:
	// コンストラクタ
	ConstIterator(const Node* node)
		: current(node) { }

	// コピーコンストラクタ
	ConstIterator(const ConstIterator& other)
		: current(other.current) { }

	// --- Get Node ---

	const Node* GetCurrent() const
	{
		return current;
	}

	Node* GetNext() const
	{
		return current->next;
	}

	Node* GetPrev() const
	{
		return current->prev;
	}

	// --- Get ScoreData ---

	ScoreData GetScoreData(Node* node)
	{
		return node->scoreData;
	}

	// --- Operators ---

	ConstIterator& operator++()
	{
		current = current->next;
		return *this;
	}

	ConstIterator& operator--()
	{
		current = current->prev;
		return *this;
	}

	const ScoreData& operator*()
	{
		return current->scoreData;
	}

	ConstIterator& operator=(const ConstIterator& other)
	{
		current = other.current;
		return *this;
	}

	bool operator==(const ConstIterator& other) const
	{
		return current == other.current;
	}

	bool operator!=(const ConstIterator& other) const
	{
		return current != other.current;
	}
};