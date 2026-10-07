#pragma once

#include "ScoreData.h"

// 双方向リスト
template <typename T>
class DoublyLinkedList
{
private:
	struct Node
	{
	private:
		T data;
		Node* prev;
		Node* next;
	public:
		Node(const T& entryData);
		T& GetData();
		const T& GetData() const;
		Node* GetPrev();
		const Node* GetPrev() const;
		Node* GetNext();
		const Node* GetNext() const;
		void SetPrev(Node* node);
		void SetNext(Node* node);
	};
public:
	class Iterator; // ConstIteratorはコンストラクタにIteratorを禁止するため
	class ConstIterator
	{
		friend class DoublyLinkedList;
	protected:
		const Node* current;
		const DoublyLinkedList* owner;
	public:
		ConstIterator(const Node* node, const DoublyLinkedList* list);
		ConstIterator(const ConstIterator& other);
		ConstIterator(const Iterator&) = delete;

		const DoublyLinkedList* GetOwner() const;

		ConstIterator& operator++();
		ConstIterator& operator++(int);
		ConstIterator& operator--();
		ConstIterator& operator--(int);
		const T& operator*() const;
		ConstIterator& operator=(const ConstIterator& other);
		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Node* node, const DoublyLinkedList* list);
		T& operator*();
		Iterator& operator++();
		Iterator& operator++(int);
		Iterator& operator--();
		Iterator& operator--(int);
	};
private:
	Node* head;
	Node* tail;
	Node  dummy;
	int count;

	// もしposition == nullptrの場合、return
	void InsertAt(Node* position, const T& data);
	void DeleteAt(Node* position);
public:
	DoublyLinkedList();
	virtual ~DoublyLinkedList();

	int GetSize() const;

	// 挿入
	void Insert(Iterator position, const T& data);
	void Insert(ConstIterator position, const T& data);

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
	// trueならリストに存在する
	// falseならリストに存在しない
	bool CheckForScore(int score);
	bool CheckForName(const std::string& name);
};

#include "DoublyLinkedList.inl"
