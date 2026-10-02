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

	// Empty list insertion
	if (head == nullptr)
	{
		head = tail = newNode;
		count++;
		return;
	}
	// Tail insertion
	if (position.GetCurrent() == nullptr)
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		count++;
		return;
	}
	// Head insertion
	if (position == head)
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
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

void DoublyLinkedList::Insert(ConstIterator position, const ScoreData& data)
{
	// Bad data is ILLEGAL
	if (data.score < 0) return;
	if (data.name == "") return;

	Node* newNode = new Node(data);

	// Empty list insertion
	if (head == nullptr)
	{
		head = tail = newNode;
		count++;
		return;
	}
	// Tail insertion
	if (position.GetCurrent() == nullptr)
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		count++;
		return;
	}
	// Head insertion
	if (position == head)
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		count++;
		return;
	}

	// Somewhere in the middle insertion - no need to handle head/tail
	Node* currentNode = const_cast<Node*>(position.GetCurrent());
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

void DoublyLinkedList::Delete(ConstIterator position) 
{ 
	if (position.GetCurrent() == nullptr) return;
	Node* target = const_cast<Node*>(position.GetCurrent());
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
Iterator DoublyLinkedList::Last() { return Iterator(tail); }
ConstIterator DoublyLinkedList::cLast() { return ConstIterator(tail); }
Iterator DoublyLinkedList::End() { return Iterator(nullptr); }
ConstIterator DoublyLinkedList::cEnd() { return ConstIterator(nullptr); }

// --- Find Node ---

Iterator DoublyLinkedList::FindByScore(int score)
{
	Node* cur = head;
	while (cur != nullptr)
	{
		if (cur->scoreData.score == score)
			return Iterator(cur);
		cur = cur->next;
	}
	return End();
}

Iterator DoublyLinkedList::FindByName(const std::string& name)
{
	Node* cur = head;
	while (cur != nullptr)
	{
		if (cur->scoreData.name == name)
			return Iterator(cur);
		cur = cur->next;
	}
	return End();
}

// --- Check for Node Parameter ---

bool DoublyLinkedList::CheckForScore(int score)
{
	for (ConstIterator it = cBegin(); it != cEnd(); ++it)
		if (it.GetCurrent()->GetScore() == score) return true;
	return false;
}

bool DoublyLinkedList::CheckForName(const std::string& name)
{
	for (ConstIterator it = cBegin(); it != cEnd(); ++it)
		if (it.GetCurrent()->GetName() == name) return true;
	return false;
}

// --- Display ---

void DoublyLinkedList::PrintForward()
{
	for (Node* cur = head; cur; cur = cur->next)
		printf("%d\t%s\n", cur->scoreData.score, cur->scoreData.name.c_str());
}
