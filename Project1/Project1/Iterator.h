#pragma once

#include "ConstIterator.h"

class Iterator : public ConstIterator
{
public:
	Iterator(Node* node)
		: ConstIterator(node) { }

	ScoreData& operator*() { }
};