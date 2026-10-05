#pragma once

#include "Node.h"

class Iterator;

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

	ConstIterator(const Iterator&) = delete;

	// --- Get Node ---

	const Node* GetCurrent() const
	{
		return current;
	}

	Node* GetNextNode() const
	{
		return current->GetNext();
	}

	Node* GetPrevNode() const
	{
		return current->GetPrev();
	}

	// --- Operators ---

	ConstIterator& operator++()
	{
		current = current->GetNext();
		return *this;
	}

	ConstIterator& operator++(int)
	{
		current = current->GetNext();
		return *this;
	}

	ConstIterator& operator--()
	{
		current = current->GetPrev();
		return *this;
	}

	ConstIterator& operator--(int)
	{
		current = current->GetPrev();
		return *this;
	}

	const ScoreData& operator*()
	{
		return current->GetData();
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