#pragma once

#include "Node.h"
#include "Iterator.h"
#include "ConstIterator.h"

// ‘o•ûŒüƒŠƒXƒg
struct DoublyLinkedList
{
private:
	Node* head;
	Node* tail;
	int count;

public:
	DoublyLinkedList();
	~DoublyLinkedList();

	int GetSize() const;

	void Insert(Iterator position, const ScoreData& data);
	void Delete(Iterator position);

	Iterator Begin();
	ConstIterator cBegin();
	Iterator End();
	ConstIterator cEnd();

	void PrintForward();
};
