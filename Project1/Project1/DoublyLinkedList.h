#pragma once

#include "ScoreData.h"

// 双方向リスト
class DoublyLinkedList
{
private:
	struct Node
	{
	private:
		ScoreData scoreData;
		Node* prev;
		Node* next;
	public:
		Node(const ScoreData& data)
			: scoreData(data), prev(nullptr), next(nullptr) {
		}
		ScoreData& GetData() { return scoreData; }
		const ScoreData& GetData() const { return scoreData; }
		Node* GetPrev() { return prev; }
		const Node* GetPrev() const { return prev; }
		Node* GetNext() { return next; }
		const Node* GetNext() const { return next; }
		void SetPrev(Node* node) { prev = node; }
		void SetNext(Node* node) { next = node; }
	};
public:
	class Iterator; // ConstIteratorはコンストラクタにIteratorを禁止するため
	class ConstIterator
	{
		friend class DoublyLinkedList;
	protected:
		const Node* current;
	public:
		ConstIterator(const Node* node)
			: current(node) {
		}
		ConstIterator(const ConstIterator& other)
			: current(other.current) {
		}
		ConstIterator(const Iterator&) = delete;

		ScoreData& GetData(Node* node) { return node->GetData(); }

		ConstIterator& operator++() { current = current->GetNext(); return *this; }
		ConstIterator& operator++(int) 
		{ 
			ConstIterator temp = *this; 
			current = current->GetNext(); 
			return temp; }
		ConstIterator& operator--() { current = current->GetPrev(); return *this; }
		ConstIterator& operator--(int) 
		{  
			ConstIterator temp = *this;
			current = current->GetPrev(); 
			return temp; 
		}
		const ScoreData& operator*() const { return current->GetData(); }
		ConstIterator& operator=(const ConstIterator& other) { current = other.current; return *this; }
		const bool operator==(const ConstIterator& other) const { return current == other.current; }
		const bool operator!=(const ConstIterator& other) const { return current != other.current; }
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Node* node)
			: ConstIterator(node) {
		}
		ScoreData& operator*() { return const_cast<Node*>(current)->GetData(); }
		Iterator& operator++() { current = current->GetNext(); return *this; }
		Iterator& operator++(int)
		{
			Iterator temp = *this;
			current = current->GetNext();
			return temp;
		}
		Iterator& operator--() { current = current->GetPrev(); return *this; }
		Iterator& operator--(int)
		{
			Iterator temp = *this;
			current = current->GetPrev();
			return temp;
		}
	};
private:
	Node* head;
	Node* tail;
	Node  dummy;
	int count;

	// もしposition == nullptrの場合、return
	void InsertAt(Node* position, const ScoreData& data);
	void DeleteAt(Node* position);
public:
	DoublyLinkedList();
	virtual ~DoublyLinkedList();

	int GetSize() const;

	// 挿入
	void Insert(Iterator position, const ScoreData& data);
	void Insert(ConstIterator position, const ScoreData& data);

	// 解除
	void Delete(Iterator position);
	void Delete(ConstIterator position);

	// 最初
	Iterator Begin();
	ConstIterator cBegin() const;

	// 最後
	Iterator Last();
	ConstIterator cLast() const;

	// 最後より+1
	Iterator End();
	ConstIterator cEnd() const;

	// スコアで探す
	Iterator FindByScore(int score);
	ConstIterator FindByScore(int score) const;

	// 名前で探す
	Iterator FindByName(const std::string& name);
	ConstIterator FindByName(const std::string& name) const;

	// スコア又は名前がリストに存在する
	bool CheckForScore(int score);
	bool CheckForName(const std::string& name);
};
