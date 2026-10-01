#pragma once

#include <fstream>
#include <string>


// リストのノード形
struct Node
{
	std::string data;
	Node* prev;
	Node* next;

	Node(const std::string& val)
		: data(val), prev(nullptr), next(nullptr) {
	}
};

// 双方向リスト
struct DoublyLinkedList
{
	Node* head;
	Node* tail;

	DoublyLinkedList();
	~DoublyLinkedList();

	void pushBack(const std::string& val);

	void printForward();
};
