#include "DoublyLinkedList.h"


DoublyLinkedList::DoublyLinkedList()
{	
	dummy = new Node(ScoreData(0, "")); // Note this is illegal data
	head  = dummy;
	tail  = dummy;
	count = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	Node* cur = head;
	while (cur != dummy)
	{
		Node* next = cur->GetNext();
		delete cur;
		cur = next;
	}
	delete dummy;
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
	if (data.GetScore() < 0) return;
	if (data.GetName() == "") return;
	
	Node* newNode = new Node(data);

	// Empty list insertion
	if (head == dummy)
	{
		newNode->SetNext(dummy);
		dummy->SetPrev(newNode);
		head = newNode;
		tail = newNode;
		count++;
		return;
	}
	// End insertion
	if (position.GetCurrent() == dummy)
	{
		newNode->SetPrev(tail);
		newNode->SetNext(dummy);
		tail->SetNext(newNode);
		dummy->SetPrev(newNode);
		tail = newNode;
		count++;
		return;
	}
	// Head insertion
	if (position.GetCurrent() == head)
	{
		newNode->SetNext(head);
		head->SetPrev(newNode);
		head = newNode;
		count++;
		return;
	}
	
	// Somewhere in the middle insertion - no need to handle head/tail
	Node* currentNode = position.GetCurrent();
	newNode->SetNext(currentNode);
	newNode->SetPrev(currentNode->GetPrev());
	currentNode->GetPrev()->SetNext(newNode);
	currentNode->SetPrev(newNode);
	count++;
	return;
}

void DoublyLinkedList::Insert(ConstIterator position, const ScoreData& data)
{
	// Bad data is ILLEGAL
	if (data.GetScore() < 0) return;
	if (data.GetName() == "") return;

	Node* newNode = new Node(data);

	// Empty list insertion
	if (head == dummy)
	{
		newNode->SetNext(dummy);
		dummy->SetPrev(newNode);
		head = newNode;
		tail = newNode;
		count++;
		return;
	}
	// End insertion
	if (position.GetCurrent() == dummy)
	{
		newNode->SetPrev(tail);
		newNode->SetNext(dummy);
		tail->SetNext(newNode);
		dummy->SetPrev(newNode);
		tail = newNode;
		count++;
		return;
	}
	// Head insertion
	if (position.GetCurrent() == head)
	{
		newNode->SetNext(head);
		head->SetPrev(newNode);
		head = newNode;
		count++;
		return;
	}

	// Somewhere in the middle insertion - no need to handle head/tail
	Node* currentNode = const_cast<Node*>(position.GetCurrent());
	newNode->SetNext(currentNode);
	newNode->SetPrev(currentNode->GetPrev());
	currentNode->GetPrev()->SetNext(newNode);
	currentNode->SetPrev(newNode);
	count++;
	return;
}

void DoublyLinkedList::Delete(Iterator position) 
{ 
	if (position.GetCurrent() == dummy) return; // 2dumb2die
	if (position.GetCurrent() == nullptr) return;
	Node* target = position.GetCurrent();
	Node* prev = target->GetPrev();
	Node* next = target->GetNext();

	if (prev == nullptr && next == dummy) // Only node
	{
		head = dummy;
		tail = dummy;
		dummy->SetPrev(nullptr);
	}
	else if (prev == nullptr && next != dummy) // Head deletion
	{
		head = next;
		next->SetPrev(nullptr);
	}
	else if (next == dummy) // Tail deletion
	{
		tail = prev;
		prev->SetNext(dummy);
		dummy->SetPrev(prev);
	}
	else
	{
		prev->SetNext(next);
		next->SetPrev(prev);
	}
	delete target;
	count--;
}

void DoublyLinkedList::Delete(ConstIterator position) 
{ 
	if (position.GetCurrent() == dummy) return; // 2dumb2die
	if (position.GetCurrent() == nullptr) return;
	Node* target = const_cast<Node*>(position.GetCurrent());
	Node* prev = target->GetPrev();
	Node* next = target->GetNext();

	if (prev == nullptr && next == dummy) // Only node
	{
		head = dummy;
		tail = dummy;
		dummy->SetPrev(nullptr);
	}
	else if (prev == nullptr && next != dummy) // Head deletion
	{
		head = next;
		next->SetPrev(nullptr);
	}
	else if (next == dummy) // Tail deletion
	{
		tail = prev;
		prev->SetNext(dummy);
		dummy->SetPrev(prev);
	}
	else
	{
		prev->SetNext(next);
		next->SetPrev(prev);
	}
	delete target;
	count--;
}

// --- Iterator/ConstIterator ---

Iterator DoublyLinkedList::Begin() { return Iterator(head); }
ConstIterator DoublyLinkedList::cBegin() const { return ConstIterator(head); }
Iterator DoublyLinkedList::Last() { return Iterator(tail); }
ConstIterator DoublyLinkedList::cLast() const { return ConstIterator(tail); }
Iterator DoublyLinkedList::End() { return Iterator(dummy); }
ConstIterator DoublyLinkedList::cEnd() const { return ConstIterator(dummy); }

// --- Find Node ---

Iterator DoublyLinkedList::FindByScore(int score)
{
	Node* cur = head;
	while (cur != dummy)
	{
		if (cur->GetData().GetScore() == score)
			return Iterator(cur);
		cur = cur->GetNext();
	}
	return End();
}

ConstIterator DoublyLinkedList::FindByScore(int score) const
{
	Node* cur = head;
	while (cur != dummy)
	{
		if (cur->GetData().GetScore() == score)
			return Iterator(cur);
		cur = cur->GetNext();
	}
	return cEnd();
}

Iterator DoublyLinkedList::FindByName(const std::string& name)
{
	Node* cur = head;
	while (cur != dummy)
	{
		if (cur->GetData().GetName() == name)
			return Iterator(cur);
		cur = cur->GetNext();
	}
	return End();
}

ConstIterator DoublyLinkedList::FindByName(const std::string& name) const
{
	Node* cur = head;
	while (cur != dummy)
	{
		if (cur->GetData().GetName() == name)
			return Iterator(cur);
		cur = cur->GetNext();
	}
	return cEnd();
}

// --- Check for Node Parameter ---

bool DoublyLinkedList::CheckForScore(int score)
{
	for (ConstIterator it = cBegin(); it != cEnd(); ++it)
		if (it.GetCurrent()->GetData().GetScore() == score) return true;
	return false;
}

bool DoublyLinkedList::CheckForName(const std::string& name)
{
	for (ConstIterator it = cBegin(); it != cEnd(); ++it)
		if (it.GetCurrent()->GetData().GetName() == name) return true;
	return false;
}

// --- Display ---

void DoublyLinkedList::PrintForward()
{
	for (Node* cur = head; cur != dummy; cur = cur->GetNext())
		printf("%d\t%s\n", cur->GetData().GetScore(), cur->GetData().GetName().c_str());
}
