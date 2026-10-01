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

int DoublyLinkedList::GetSize() const
{
	return count;
}

// --- Node Management ---

void DoublyLinkedList::Insert(Iterator position, const ScoreData& data) 
{ 
	// Bad data is ILLEGAL
	if (data.score < 0) return;
	if (data.name == "") return;
	
	Node* newNode = new Node(data);

	// Head insertion
	if (head == nullptr)
	{
		head = tail = newNode;
		count++;
		return;
	}
	// Tail insertion
	if (position == tail)
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		count++;
		return;
	}
	
	// Somewhere in the middle insertion - no need to handle head/tail
	Node* currentNode = position.GetCurrent();
	newNode->next = currentNode;
	newNode->prev = currentNode->prev;
	currentNode->prev->next = newNode;
	currentNode->prev = newNode;
	count++;
	return;
}

void DoublyLinkedList::Delete(Iterator position) 
{ 
	if (position.GetCurrent() == nullptr) return;
	Node* target = position.GetCurrent();
	Node* prev = target->prev;
	Node* next = target->next;

	if (prev == nullptr && next == nullptr) // Only node
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (prev == nullptr && next != nullptr) // Head deletion
	{
		head = next;
		next->prev = nullptr;
	}
	else if (prev != nullptr && next == nullptr) // Tail deletion
	{
		tail = prev;
		prev->next = nullptr;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
	}
	delete target;
	count--;
}

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
