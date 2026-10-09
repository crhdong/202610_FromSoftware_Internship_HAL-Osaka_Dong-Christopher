#pragma once

#include "ScoreData.h"

/// 双方向リスト
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
	class Iterator; /// ConstIteratorはコンストラクタにIteratorを禁止するため
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

		ConstIterator operator++();
		ConstIterator operator++(int);
		ConstIterator operator--();
		ConstIterator operator--(int);
		const T& operator*() const;
		ConstIterator operator=(const ConstIterator& other);
		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Node* node, const DoublyLinkedList* list);
		T& operator*();
		Iterator operator++();
		Iterator operator++(int);
		Iterator operator--();
		Iterator operator--(int);
	};
private:
	Node* head;
	Node* tail;
	Node  dummy;
	int count;

	/// --- プライベート用関数 ---
	
	/// 呼びたいならInsert()を呼んでください
	void InsertAt(Node* position, const T& data);
	/// 呼びたいならDelete()を呼んでください
	void DeleteAt(Node* position);
public:
	DoublyLinkedList();
	virtual ~DoublyLinkedList();

	/// --- ノード数 ---
	
	/// ノードの数を取得
	/// dummyのノードは計算しない
	int GetSize() const;

	/// ---　挿入　---
	
	/// イテレータ一位の前に新しいノードを挿入する
	/// count++
	/// nullptrとdummyが渡した場合、新しい末尾になる
	/// 別リストのイテレータで追加できない（return）
	/// TRUE = 成功, FALSE = 失敗
	bool Insert(Iterator position, const T& data);
	/// イテレータ一位の前に新しいノードを挿入する
	/// count++
	/// nullptrとdummyが渡した場合、新しい末尾になる
	/// 別リストのイテレータで追加できない（return）
	/// TRUE = 成功, FALSE = 失敗
	bool Insert(ConstIterator position, const T& data);

	/// 解除
	
	/// イテレータ一位でノードを解除する
	/// count--
	/// nullptrとdummyが渡した場合、直ぐreturn
	/// 別リストのイテレータで解除できない（return）
	/// TRUE = 成功, FALSE = 失敗
	bool Delete(Iterator position);
	/// イテレータ一位でノードを解除する
	/// count--
	/// nullptrとdummyが渡した場合、直ぐreturn
	/// 別リストのイテレータで解除できない（return）
	/// TRUE = 成功, FALSE = 失敗
	bool Delete(ConstIterator position);

	/// 先頭
	
	/// 先頭のイテレータを返す
	Iterator Begin();
	/// 先頭のイテレータを返す
	ConstIterator cBegin() const;

	/// 末尾
	/// 末尾のイテレータを返す
	Iterator Last();
	/// 末尾のイテレータを返す
	ConstIterator cLast() const;

	/// 末尾+1（dummy）
	
	/// 末尾 + 1 のイテレータを返す
	/// いつもdummy
	Iterator End();
	/// 末尾 + 1 のイテレータを返す
	/// いつもdummy
	ConstIterator cEnd() const;

	/// スコアで探す
	/// 先頭からパスしたパラメーターを探す
	/// 見つからない場合 End() を返す
	Iterator FindByScore(int score);
	/// スコアで探す
	/// 先頭からパスしたパラメーターを探す
	/// 見つからない場合 End() を返す
	ConstIterator FindByScore(int score) const;

	/// ---　名前で探す　---
	
	/// 先頭からパスしたパラメーターを探す
	/// 見つからない場合 End() を返す
	Iterator FindByName(const std::string& name);
	/// 先頭からパスしたパラメーターを探す
	/// 見つからない場合 End() を返す
	ConstIterator FindByName(const std::string& name) const;

	/// ---　データ存在探し　---
	
	/// 渡したパラメーターが持つノードの存在を探す
	/// ノードのイテレータが欲しいならFind関数を使ってください
	bool CheckForScore(int score);
	/// 渡したパラメーターが持つノードの存在を探す
	/// ノードのイテレータが欲しいならFind関数を使ってください
	bool CheckForName(const std::string& name);
};

#include "DoublyLinkedList.inl"