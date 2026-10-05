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
		newNode->SetRNext(dummy);
		dummy->SetRPrev(newNode);
		head = newNode;
		tail = newNode;
		count++;
		return;
	}
	// End (Head) insertion
	if (position.GetCurrent() == dummy)
	{
		newNode->SetRPrev(head);
		newNode->SetRNext(dummy);
		head->SetRNext(newNode);
		dummy->SetRPrev(newNode);
		head = newNode;
		count++;
		return;
	}
	// Head (Tail) insertion
	if (position.GetCurrent() == tail)
	{
		newNode->SetRNext(tail);
		tail->SetRPrev(newNode);
		tail = newNode;
		count++;
		return;
	}

	// Somewhere in the middle insertion - no need to handle head/tail
	Node* currentNode = const_cast<Node*>(position.GetCurrent());
	newNode->SetRNext(currentNode);
	newNode->SetRPrev(currentNode->GetRPrev());
	currentNode->GetRPrev()->SetRNext(newNode);
	currentNode->SetRPrev(newNode);
	count++;
	return;
}
void DoublyLinkedList::Insert(ReverseIterator position, const ScoreData& data)
{
	// Bad data is ILLEGAL
	if (data.GetScore() < 0) return;
	if (data.GetName() == "") return;

	Node* newNode = new Node(data);

	// Empty list insertion
	if (tail == dummy)
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
void DoublyLinkedList::Insert(ReverseConstIterator position, const ScoreData& data)
{
	// Bad data is ILLEGAL
	if (data.GetScore() < 0) return;
	if (data.GetName() == "") return;

	Node* newNode = new Node(data);

	// Empty list insertion
	if (tail == dummy)
	{
		newNode->SetRNext(dummy);
		dummy->SetRPrev(newNode);
		head = newNode;
		tail = newNode;
		count++;
		return;
	}
	// End insertion
	if (position.GetCurrent() == dummy)
	{
		newNode->SetRPrev(head);
		newNode->SetRNext(dummy);
		head->SetRNext(newNode);
		dummy->SetRPrev(newNode);
		head = newNode;
		count++;
		return;
	}
	// Head insertion
	if (position.GetCurrent() == tail)
	{
		newNode->SetRNext(tail);
		tail->SetRPrev(newNode);
		tail = newNode;
		count++;
		return;
	}

	// Somewhere in the middle insertion - no need to handle head/tail
	Node* currentNode = const_cast<Node*>(position.GetCurrent());
	newNode->SetRNext(currentNode);
	newNode->SetRPrev(currentNode->GetRPrev());
	currentNode->GetRPrev()->SetRNext(newNode);
	currentNode->SetRPrev(newNode);
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
void DoublyLinkedList::Delete(ReverseIterator position) 
{ 
	if (position.GetCurrent() == dummy) return; // 2dumb2die
	if (position.GetCurrent() == nullptr) return;
	Node* target = position.GetCurrent();
	Node* prev = target->GetRPrev();
	Node* next = target->GetRNext();

	if (prev == nullptr && next == dummy) // Only node
	{
		head = dummy;
		tail = dummy;
		dummy->SetRPrev(nullptr);
	}
	else if (prev == nullptr && next != dummy) // Head (Tail) deletion
	{
		tail = next;
		next->SetRPrev(nullptr);
	}
	else if (next == dummy) // Tail (Head) deletion
	{
		head = prev;
		prev->SetRNext(dummy);
		dummy->SetRPrev(prev);
	}
	else
	{
		prev->SetRNext(next);
		next->SetRPrev(prev);
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
void DoublyLinkedList::Delete(ReverseConstIterator position) 
{ 
	if (position.GetCurrent() == dummy) return; // 2dumb2die
	if (position.GetCurrent() == nullptr) return;
	Node* target = const_cast<Node*>(position.GetCurrent());
	Node* prev = target->GetRPrev();
	Node* next = target->GetRNext();

	if (prev == nullptr && next == dummy) // Only node
	{
		head = dummy;
		tail = dummy;
		dummy->SetRPrev(nullptr);
	}
	else if (prev == nullptr && next != dummy) // Head (Tail) deletion
	{
		head = next;
		next->SetRPrev(nullptr);
	}
	else if (next == dummy) // Tail (Head) deletion
	{
		tail = prev;
		prev->SetRNext(dummy);
		dummy->SetRPrev(prev);
	}
	else
	{
		prev->SetRNext(next);
		next->SetRPrev(prev);
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

ReverseIterator DoublyLinkedList::rBegin() { return ReverseIterator(head); }
ReverseConstIterator DoublyLinkedList::rcBegin() const { return ReverseConstIterator(head); }
ReverseIterator DoublyLinkedList::rLast() { return ReverseIterator(tail); }
ReverseConstIterator DoublyLinkedList::rcLast() const { return ReverseConstIterator(tail); }
ReverseIterator DoublyLinkedList::rEnd() { return ReverseIterator(dummy); }
ReverseConstIterator DoublyLinkedList::rcEnd() const { return ReverseConstIterator(dummy); }

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
			return ConstIterator(cur);
		cur = cur->GetNext();
	}
	return cEnd();
}
ReverseIterator DoublyLinkedList::FindByScoreReverse(int score)
{
	Node* cur = tail;
	while (cur != head->GetRNext())
	{
		if (cur->GetData().GetScore() == score)
			return ReverseIterator(cur);
		cur = cur->GetNext();
	}
	return rEnd();
}
ReverseConstIterator DoublyLinkedList::FindByScoreReverse(int score) const
{
	Node* cur = tail;
	while (cur != head->GetRNext())
	{
		if (cur->GetData().GetScore() == score)
			return ReverseConstIterator(cur);
		cur = cur->GetRNext();
	}
	return rcEnd();
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
			return ConstIterator(cur);
		cur = cur->GetNext();
	}
	return cEnd();
}
ReverseIterator DoublyLinkedList::FindByNameReverse(const std::string& name)
{
	Node* cur = tail;
	while (cur != head->GetRNext())
	{
		if (cur->GetData().GetName() == name)
			return ReverseIterator(cur);
		cur = cur->GetRNext();
	}
	return rEnd();
}
ReverseConstIterator DoublyLinkedList::FindByNameReverse(const std::string& name) const
{
	Node* cur = tail;
	while (cur != head->GetRNext())
	{
		if (cur->GetData().GetName() == name)
			return ReverseConstIterator(cur);
		cur = cur->GetRNext();
	}
	return rcEnd();
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
void DoublyLinkedList::PrintBackward()
{
	for (Node* cur = tail; cur != head->GetRNext(); cur = cur->GetRNext())
		printf("%d\t%s\n", cur->GetData().GetScore(), cur->GetData().GetName().c_str());
}
