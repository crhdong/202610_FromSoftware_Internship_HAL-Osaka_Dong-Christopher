#pragma once

#include "ReverseConstIterator.h"

class ReverseIterator : public ReverseConstIterator
{
public:
	ReverseIterator(Node* node)
		: ReverseConstIterator(node) {
	}

	ScoreData& operator*()
	{
		return const_cast<Node*>(current)->GetData();
	}

	Node* GetCurrent()
	{
		return const_cast<Node*>(current);
	}

	Node* GetNext()
	{
		return current->GetPrev();
	}

	Node* GetPrev()
	{
		return current->GetNext();
	}
};