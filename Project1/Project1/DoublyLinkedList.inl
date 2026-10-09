#pragma once

#include "DoublyLinkedList.h"
#define TEMPLATE template <typename T>
#define DLL DoublyLinkedList<T>
#define DLLN DoublyLinkedList<T>::Node
#define DLLCIt DoublyLinkedList<T>::ConstIterator
#define DLLIt DoublyLinkedList<T>::Iterator

/******************/
/***** ノード　*****/
/******************/

/// コンストラクタ
template <typename T>
DoublyLinkedList<T>::Node::Node(const T& entryData)
	: data(entryData), prev(nullptr), next(nullptr) { }

/// --- データ取得 ---

TEMPLATE
T& DLLN::GetData() { return data; }

TEMPLATE
const T& DLLN::GetData() const { return data; }

/// --- ノード取得 ---

TEMPLATE
typename DLLN* DLLN::GetPrev() { return prev; }

TEMPLATE
const typename DLLN* DLLN::GetPrev() const { return prev; }

TEMPLATE
typename DLLN* DLLN::GetNext() { return next; }

TEMPLATE
const typename DLLN* DLLN::GetNext() const { return next; }

/// ノード上書き

TEMPLATE
void DLLN::SetPrev(Node* node) { prev = node; }

TEMPLATE
void DLLN::SetNext(Node* node) { next = node; }

/****************************/
/***** コンストイテレータ　*****/ 
/****************************/

/// --- コンストラクタ ---

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const DLL::Node* node, const DoublyLinkedList<T>* list)
	: current(node), owner(list) { }

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const ConstIterator& other)
	: current(other.current), owner(other.owner) { }

///TEMPLATE
///DLLCIt::ConstIterator(const Iterator&) = delete;

/// --- オーナー ---

TEMPLATE
const typename DLL* DLLCIt::GetOwner() const
{
	return owner;
}

/// --- ノードoperator ---

TEMPLATE
typename DLLCIt DLLCIt::operator++()
{
	if (current != nullptr)
	{
		current = current->GetNext();
	}
	return *this;
}

TEMPLATE
typename DLLCIt DLLCIt::operator++(int)
{
	ConstIterator temp = *this;
	if (current != nullptr)
	{
		current = current->GetNext();
	}
	return temp;
}

TEMPLATE
typename DLLCIt DLLCIt::operator--()
{
	if (current != nullptr)
	{
		current = current->GetPrev();
	}
	return *this;
}

TEMPLATE
typename DLLCIt DLLCIt::operator--(int)
{
	ConstIterator temp = *this;
	if (current != nullptr)
	{
		current = current->GetPrev();
	}
	return temp;
}

TEMPLATE
const T& DLLCIt::operator*() const
{ 
	return current->GetData();
}

TEMPLATE
typename DLLCIt DLLCIt::operator=(const ConstIterator& other)
{
	current = other.current;
	owner = other.owner;
	return *this;
}

TEMPLATE
bool DLLCIt::operator==(const ConstIterator& other) const
{
	return current == other.current;
}

TEMPLATE
bool DLLCIt::operator!=(const ConstIterator& other) const
{
	return current != other.current;
}

/**********************/
/*****　イテレータ　*****/
/**********************/

/// コンストラクタ

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node, const DoublyLinkedList<T>* list)
	: ConstIterator(node, list) { }

/// ノードoperator

TEMPLATE
T& DLLIt::operator*()
{
	return const_cast<Node*>(DLL::Iterator::current)->GetData();
}

TEMPLATE
typename DLLIt DLLIt::operator++()
{
	if (DLLIt::current != nullptr)
	{
		DLLIt::current = DLLIt::current->GetNext();
	}
	return *this;
}

TEMPLATE
typename DLLIt DLLIt::operator++(int)
{
	Iterator temp = *this;
	if (DLLIt::current != nullptr)
	{
		DLLIt::current = DLLIt::current->GetNext();
	}
	return temp;
}

TEMPLATE
typename DLLIt DLLIt::operator--()
{
	if (DLLIt::current != nullptr)
	{
		DLLIt::current = DLLIt::current->GetPrev();
	}
	return *this;
}

TEMPLATE
typename DLLIt DLLIt::operator--(int)
{
	Iterator temp = *this;
	if (DLLIt::current != nullptr)
	{
		DLLIt::current = DLLIt::current->GetPrev();
	}
	return temp;
}

/****************************/
/***** DoublyLinkedList *****/
/****************************/

/// --- コンストラクタ ---
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
	: dummy(T{}), head(&dummy), tail(&dummy), count(0) 
{
	dummy.SetNext(&dummy);
	dummy.SetPrev(&dummy);
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Node* cur = head;
	while (cur != &dummy)
	{
		Node* next = cur->GetNext();
		delete cur;
		cur = next;
	}
}


/// --- プライベート用関数 ---
/// 呼びたいならInsert()またはDelete()を呼んでください
/// もしposition == nullptrの場合、return
TEMPLATE
void DLL::InsertAt(Node* position, const T& data)
{
	if (position == nullptr) return;

	Node* newNode = new Node(data);

	// Empty list insertion
	if (head == &dummy)
	{
		newNode->SetNext(&dummy);
		dummy.SetPrev(newNode);
		head = newNode;
		tail = newNode;
		count++;
		return;
	}

	// End insertion
	if (position == &dummy)
	{
		newNode->SetPrev(tail);
		newNode->SetNext(&dummy);
		tail->SetNext(newNode);
		dummy.SetPrev(newNode);
		tail = newNode;
		count++;
		return;
	}
	// Head insertion
	if (position == head)
	{
		newNode->SetNext(head);
		head->SetPrev(newNode);
		head = newNode;
		count++;
		return;
	}

	// Somewhere in the middle insertion - no need to handle tail
	Node* currentNode = const_cast<Node*>(position);
	newNode->SetNext(currentNode);
	newNode->SetPrev(currentNode->GetPrev());
	currentNode->GetPrev()->SetNext(newNode);
	currentNode->SetPrev(newNode);
	count++;
	return;
}
TEMPLATE
void DLL::DeleteAt(Node* position)
{
	if (position == &dummy) return; // 2dumb2die
	if (position == nullptr) return;
	Node* target = const_cast<Node*>(position);
	Node* prev = target->GetPrev();
	Node* next = target->GetNext();

	if (prev == nullptr && next == &dummy) // Only node
	{
		head = &dummy;
		tail = &dummy;
		dummy.SetPrev(nullptr);
	}
	else if (prev == nullptr && next != &dummy) // Head deletion
	{
		head = next;
		next->SetPrev(nullptr);
	}
	else if (next == &dummy) // Tail deletion
	{
		tail = prev;
		prev->SetNext(&dummy);
		dummy.SetPrev(prev);
	}
	else
	{
		prev->SetNext(next);
		next->SetPrev(prev);
	}
	delete target;
	count--;
}

/// --- ノード数 ---
/// ノードの数を返す
/// dummyのノードは計算しない
TEMPLATE
int DLL::GetSize() const
{
	return count;
}

/// --- ノード挿入と解除 ---
/// イテレータ一位の前に新しいノードを挿入する
/// count++
/// nullptrとdummyが渡した場合、新しい末尾になる
/// 別リストのイテレータで追加できない（return）
/// TRUE = 成功, FALSE = 失敗
TEMPLATE
bool DLL::Insert(ConstIterator position, const T& data)
{
	if (position.current == nullptr) return false;
	if (position.GetOwner() != this) return false;
	InsertAt(const_cast<Node*>(position.current), data);
	return true;
}
TEMPLATE
bool DLL::Insert(Iterator position, const T& data)
{
	if (position.current == nullptr) return false;
	if (position.GetOwner() != this) return false;
	InsertAt(const_cast<Node*>(position.current), data);
	return true;
}

/// イテレータ一位でノードを解除する
/// count--
/// nullptrとdummyが渡した場合、直ぐreturn
/// 別リストのイテレータで解除できない（return）
/// TRUE = 成功, FALSE = 失敗
TEMPLATE
bool DLL::Delete(ConstIterator position)
{
	if (position.current == nullptr) return false;
	if (position.GetOwner() != this) return false;
	if (position.current == &dummy) return false;
	DeleteAt(const_cast<Node*>(position.current));
	return true;
}
TEMPLATE
bool DLL::Delete(Iterator position)
{
	if (position.current == nullptr) return false;
	if (position.GetOwner() != this) return false;
	if (position.current == &dummy) return false;
	DeleteAt(const_cast<Node*>(position.current));
	return true;
}

/// --- イテレータ・コンストイテレータ ---

/// Beginは先頭のイテレータを返す
/// Last は末尾のイテレータを返す
/// End  は末尾 + 1 のイテレータを返す
TEMPLATE
typename DLLIt DLL::Begin() { return Iterator(head, this); }
TEMPLATE
typename DLLCIt DLL::cBegin() const { return ConstIterator(head, this); }
TEMPLATE
typename DLLIt DLL::Last() { return Iterator(tail, this); }
TEMPLATE
typename DLLCIt DLL::cLast() const { return ConstIterator(tail, this); }
TEMPLATE
typename DLLIt DLL::End() { return Iterator(&dummy, this); }
TEMPLATE
typename DLLCIt DLL::cEnd() const { return ConstIterator(&dummy, this); }

/// --- ノード探し ---
/// 先頭からパスしたパラメーターを探す
/// 見つからない場合 End() を返す
TEMPLATE
typename DLLIt DLL::FindByScore(int score)
{
	Node* cur = head;
	while (cur != &dummy)
	{
		if (cur->GetData().GetScore() == score)
			return Iterator(cur);
		cur = cur->GetNext();
	}
	return End();
}
TEMPLATE
typename DLLCIt DLL::FindByScore(int score) const
{
	Node* cur = head;
	while (cur != &dummy)
	{
		if (cur->GetData().GetScore() == score)
			return ConstIterator(cur);
		cur = cur->GetNext();
	}
	return cEnd();;
}

TEMPLATE
typename DLLIt DLL::FindByName(const std::string& name)
{
	Node* cur = head;
	while (cur != &dummy)
	{
		if (cur->GetData().GetName() == name)
			return Iterator(cur, this);
		cur = cur->GetNext();
	}
	return End();
}
TEMPLATE
typename DLLCIt DLL::FindByName(const std::string& name) const
{
	Node* cur = head;
	while (cur != &dummy)
	{
		if (cur->GetData().GetName() == name)
			return ConstIterator(cur, this);
		cur = cur->GetNext();
	}
	return cEnd();
}

/// --- データ存在探し ---
/// パスしたパラメーターが持つノードの存在を探す
/// ノードのイテレータが欲しいなら上のFind関数を使ってください
TEMPLATE
bool DLL::CheckForScore(int score)
{
	for (ConstIterator it = cBegin(); it != cEnd(); ++it)
		if ((*it).GetScore() == score) return true;
	return false;
}
TEMPLATE
bool DLL::CheckForName(const std::string& name)
{
	for (ConstIterator it = cBegin(); it != cEnd(); ++it)
		if ((*it).GetName() == name) return true;
	return false;
}