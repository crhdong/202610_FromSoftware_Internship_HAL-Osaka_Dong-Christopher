#pragma once

#include <fstream>
#include <string>


struct ScoreData
{
	int score;
	std::string name;

	ScoreData(int i, const std::string& s)
		: score(i), name(s) { }
};

// リストのノード形
struct Node
{
	ScoreData scoreData;
	Node* prev;
	Node* next;

	Node(const ScoreData& data)
		: scoreData(data), prev(nullptr), next(nullptr) { }
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
