#include "DoublyLinkedList.h"


DoublyLinkedList::DoublyLinkedList()
{
	head = nullptr;
	tail = nullptr;
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

void DoublyLinkedList::pushBack(const std::string& val)
{
	Node* newNode = new Node(val);
	if (tail == nullptr)
	{
		head = tail = newNode;
	}
	else
	{
		newNode->prev = tail;
		tail->next	  = newNode;
		tail		  = newNode;
	}
}

void DoublyLinkedList::printForward()
{
	for (Node* cur = head; cur; cur = cur->next)
	{ 
		const char* result = cur->data.c_str();
		printf("%s\n", result);
	}	
}