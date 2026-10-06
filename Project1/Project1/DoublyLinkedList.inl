#pragma once

#include "DoublyLinkedList.h"

// -------------
// --- ノード ---
// -------------

// コンストラクタ
template <typename T>
DoublyLinkedList<T>::Node::Node(const T& entryData)
	: data(entryData), prev(nullptr), next(nullptr) { }

// データ取得

template <typename T>
T& DoublyLinkedList<T>::Node::GetData() { return data; }

template <typename T>
const T& DoublyLinkedList<T>::Node::GetData() const { return data; }

// ノード取得

template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Node::GetPrev() { return prev; }

template <typename T>
const typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Node::GetPrev() const { return prev; }

template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Node::GetNext() { return next; }

template <typename T>
const typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Node::GetNext() const { return next; }

// ノード上書き

template <typename T>
void DoublyLinkedList<T>::Node::SetPrev(DoublyLinkedList<T>::Node* node) { prev = node; }

template <typename T>
void DoublyLinkedList<T>::Node::SetNext(DoublyLinkedList<T>::Node* node) { next = node; }

// -----------------------
// --- コンストイテレータ ---
// -----------------------

// コンストラクタ

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const Node* node)
	: current(node) { }

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const ConstIterator& other)
	: current(other.current) { }

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const Iterator&) = delete;

// ノードoperator

template <typename T>
DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++()
{
	current = current->GetNext(); 
	return *this;
}

template <typename T>
DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++(int)
{
	ConstIterator temp = *this;
	current = current->GetNext();
	return temp;
}

template <typename T>
DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--()
{
	current = current->GetPrev();
	return *this;
}

template <typename T>
DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--(int)
{
	ConstIterator temp = *this;
	current = current->GetPrev();
	return temp;
}

template <typename T>
const T& DoublyLinkedList<T>::ConstIterator::operator*() const { return current->GetData(); }

template <typename T>
DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator=
	(const ConstIterator& other)
{
	current = other.current;
	return *this;
}

template <typename T>
const bool DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const
{
	return current == other.current;
}

template <typename T>
const bool DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
	return current != other.current;
}

// -----------------
// --- イテレータ ---
// -----------------

// コンストラクタ

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node)
	: ConstIterator(node) { }

// Operators

template <typename T>
DoublyLinkedList<T>::Iterator::T& 