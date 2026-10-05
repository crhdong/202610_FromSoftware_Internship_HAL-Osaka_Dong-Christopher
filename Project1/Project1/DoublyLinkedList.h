#pragma once

#include "Node.h"
#include "Iterator.h"
#include "ConstIterator.h"
#include "ReverseIterator.h"
#include "ReverseConstIterator.h"

// ëoï˚å¸ÉäÉXÉg
struct DoublyLinkedList
{
private:
	Node* head;
	Node* tail;
	Node* dummy;
	int count;

public:
	DoublyLinkedList();
	~DoublyLinkedList();

	int GetSize() const;

	// ë}ì¸
	void Insert(Iterator position, const ScoreData& data);
	void Insert(ConstIterator position, const ScoreData& data);
	void Insert(ReverseIterator position, const ScoreData& data);
	void Insert(ReverseConstIterator position, const ScoreData& data);

	// âèú
	void Delete(Iterator position);
	void Delete(ConstIterator position);
	void Delete(ReverseIterator position);
	void Delete(ReverseConstIterator position);

	// ç≈èâ
	Iterator Begin();
	ConstIterator cBegin() const;
	ReverseIterator rBegin();
	ReverseConstIterator rcBegin() const;
	// ç≈å„
	Iterator Last();
	ConstIterator cLast() const;
	ReverseIterator rLast();
	ReverseConstIterator rcLast() const;
	// ç≈å„ÇÊÇË+1
	Iterator End();
	ConstIterator cEnd() const;
	ReverseIterator rEnd();
	ReverseConstIterator rcEnd() const;

	// ÉXÉRÉAÇ≈íTÇ∑
	Iterator FindByScore(int score);
	ConstIterator FindByScore(int score) const;
	ReverseIterator FindByScoreReverse(int score);
	ReverseConstIterator FindByScoreReverse(int score) const;
	// ñºëOÇ≈íTÇ∑
	Iterator FindByName(const std::string& name);
	ConstIterator FindByName(const std::string& name) const;
	ReverseIterator FindByNameReverse(const std::string& name);
	ReverseConstIterator FindByNameReverse(const std::string& name) const;

	bool CheckForScore(int score);
	bool CheckForName(const std::string& name);

	void PrintForward();
	void PrintBackward();
};
