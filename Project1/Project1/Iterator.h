#pragma once

#include "ConstIterator.h"

class Iterator : public ConstIterator
{
public:
	Iterator(Node* node)
		: ConstIterator(node) { }

	ScoreData& operator*() 
	{ 
		return const_cast<Node*>(current)->scoreData;
	}

	Node* GetCurrent()
	{
		return const_cast<Node*>(current);
	}
};