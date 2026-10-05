#pragma once

#include "Node.h"


class ReverseConstIterator
{
protected:
	const Node* current;

public:
	ReverseConstIterator(const Node* node)
		: current(node) { }

	ReverseConstIterator(const ReverseConstIterator& other)
		: current(other.current) { }

	// --- Get Node ---

	const Node* GetCurrent() const
	{
		return current;
	}

	Node* GetNext() const
	{
		return current->GetPrev();
	}

	Node* GetPrev() const
	{
		return current->GetNext();
	}

	// --- Get ScoreData ---

	ScoreData GetScoreData(Node* node)
	{
		return node->GetData();
	}

	// --- Operators ---

	ReverseConstIterator& operator++()
	{
		current = current->GetPrev();
		return *this;
	}

	ReverseConstIterator& operator++(int)
	{
		current = current->GetPrev();
		return *this;
	}

	ReverseConstIterator& operator--()
	{
		current = current->GetNext();
		return *this;
	}

	const ScoreData& operator*()
	{
		return current->GetData();
	}

	ReverseConstIterator& operator=(const ReverseConstIterator& other)
	{
		current = other.current;
		return *this;
	}

	bool operator==(const ReverseConstIterator& other) const
	{
		return current == other.current;
	}

	bool operator!=(const ReverseConstIterator& other) const
	{
		return current != other.current;
	}
};