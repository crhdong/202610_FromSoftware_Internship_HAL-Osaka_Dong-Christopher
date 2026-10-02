#pragma once

#include "Node.h"
#include "Iterator.h"
#include "ConstIterator.h"

// ëoï˚å¸ÉäÉXÉg
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
	void Insert(ConstIterator position, const ScoreData& data);
	void Delete(Iterator position);
	void Delete(ConstIterator position);

	// ç≈èâ
	Iterator Begin();
	ConstIterator cBegin();
	// ç≈å„
	Iterator Last();
	ConstIterator cLast();
	// ç≈å„ÇÊÇË+1
	Iterator End();
	ConstIterator cEnd();

	Iterator FindByScore(int score);
	Iterator FindByName(const std::string& name);

	bool CheckForScore(int score);
	bool CheckForName(const std::string& name);

	void PrintForward();
};
