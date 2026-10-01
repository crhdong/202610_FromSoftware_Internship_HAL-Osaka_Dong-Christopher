#include "DoublyLinkedList.h"


DoublyLinkedList::DoublyLinkedList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	Node* cur = head;
	while (cur)
	{
		Node* next = cur->next;
		delete cur;
		cur = next;
	}
}

// --- Size ---

int DoublyLinkedList::GetSize()
{
	return size;
}

// --- Node Management ---

void DoublyLinkedList::Insert(Iterator position, const ScoreData& data) { }

void DoublyLinkedList::Delete(Iterator position) { }

// --- Iterator/ConstIterator ---

Iterator DoublyLinkedList::Begin() { return Iterator(head); }
ConstIterator DoublyLinkedList::cBegin() { return ConstIterator(head); }
Iterator DoublyLinkedList::End() { return Iterator(nullptr); }
ConstIterator DoublyLinkedList::cEnd() { return ConstIterator(nullptr); }

// --- Display ---

void DoublyLinkedList::PrintForward()
{
	for (Node* cur = head; cur; cur = cur->next)
		printf("%d\t%s\n", cur->scoreData.score, cur->scoreData.name.c_str());
}
