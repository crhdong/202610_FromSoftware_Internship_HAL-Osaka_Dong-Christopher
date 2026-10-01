#include "DoublyLinkedList.h"


// --- Helpers ---

// Find where the space between the score and name is.
static int strToInt(const std::string& s, size_t& endPos)
{
	int result = 0;
	endPos = 0;

	while (endPos < s.size() && s[endPos] >= '0' && s[endPos] <= '9')
	{
		result = result * 10 + (s[endPos] - '0');
		endPos++;
	}
	return result;
}

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
	size_t space = 0;
	int score = strToInt(val, space);

	if (space >= val.size() || val[space] != '\t') return;

	std::string name = val.substr(space + 1);

	ScoreData data(score, name);
	Node* newNode = new Node(data);

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
		printf("%d\t%s\n", cur->scoreData.score, cur->scoreData.name.c_str());
}
