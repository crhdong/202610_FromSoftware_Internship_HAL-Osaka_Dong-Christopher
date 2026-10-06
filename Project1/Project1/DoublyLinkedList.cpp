#include "DoublyLinkedList.h"

// コンストラクタとディストラクタ

// ノートdummyは不良データ
DoublyLinkedList::DoublyLinkedList()
	: dummy(ScoreData(0, "")), head(&dummy), tail(&dummy), count(0) { }
DoublyLinkedList::~DoublyLinkedList()
{
	Node* cur = head;
	while (cur != &dummy)
	{
		Node* next = cur->GetNext();
		delete cur;
		cur = next;
	}
}

// --- プライベート用 ---
// プライベート用の関数
// 呼びたいならInsert()またはDelete()を呼んでください
// もしposition == nullptrの場合、return
void DoublyLinkedList::InsertAt(Node* position, const ScoreData& data)
{
	// 不良データは死刑
	if (data.GetScore() < 0) return;
	if (data.GetName() == "") return;
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

	// Somewhere in the middle insertion - no need to handle head/tail
	Node* currentNode = const_cast<Node*>(position);
	newNode->SetNext(currentNode);
	newNode->SetPrev(currentNode->GetPrev());
	currentNode->GetPrev()->SetNext(newNode);
	currentNode->SetPrev(newNode);
	count++;
	return;
}
void DoublyLinkedList::DeleteAt(Node* position)
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

// --- ノード数 ---
// ノードの数を返す
// dummyのノードは計算しない
int DoublyLinkedList::GetSize() const
{
	return count;
}

// --- ノード挿入と解除 ---
// イテレータ一位の前に新しいノードを挿入する
// count++
// nullptrとdummyが渡した場合、新しい末尾になる
// 不良データが追加できない
void DoublyLinkedList::Insert(ConstIterator position, const ScoreData& data)
{
	InsertAt(const_cast<Node*>(position.GetCurrent()), data);
}
void DoublyLinkedList::Insert(Iterator position, const ScoreData& data) 
{ 
	InsertAt(position.GetCurrent(), data);
}

// イテレータ一位でノードを解除する
// count--
// nullptrとdummyが渡した場合、直ぐreturn
void DoublyLinkedList::Delete(ConstIterator position)
{
	DeleteAt(const_cast<Node*>(position.GetCurrent()));
}
void DoublyLinkedList::Delete(Iterator position)
{
	DeleteAt(position.GetCurrent());
}

// --- イテレータ・コンストイテレータ ---

// Beginは先頭のイテレータを返す
// Last は末尾のイテレータを返す
// End  は末尾 + 1 のイテレータを返す
DoublyLinkedList::Iterator DoublyLinkedList::Begin() { return Iterator(head); }
DoublyLinkedList::ConstIterator DoublyLinkedList::cBegin() const { return ConstIterator(head); }
DoublyLinkedList::Iterator DoublyLinkedList::Last() { return Iterator(tail); }
DoublyLinkedList::ConstIterator DoublyLinkedList::cLast() const { return ConstIterator(tail); }
DoublyLinkedList::Iterator DoublyLinkedList::End() { return Iterator(&dummy); }
DoublyLinkedList::ConstIterator DoublyLinkedList::cEnd() const { return ConstIterator(&dummy); }

// --- ノード探し ---
// 先頭からパスしたパラメーターを探す
// 見つからない場合 End() を返す
DoublyLinkedList::Iterator DoublyLinkedList::FindByScore(int score)
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
DoublyLinkedList::ConstIterator DoublyLinkedList::FindByScore(int score) const
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

DoublyLinkedList::Iterator DoublyLinkedList::FindByName(const std::string& name)
{
	Node* cur = head;
	while (cur != &dummy)
	{
		if (cur->GetData().GetName() == name)
			return Iterator(cur);
		cur = cur->GetNext();
	}
	return End();
}
DoublyLinkedList::ConstIterator DoublyLinkedList::FindByName(const std::string& name) const
{
	Node* cur = head;
	while (cur != &dummy)
	{
		if (cur->GetData().GetName() == name)
			return ConstIterator(cur);
		cur = cur->GetNext();
	}
	return cEnd();
}

// --- データ存在探し ---
// パスしたパラメーターが持つノードの存在を探す
// ノードのイテレータが欲しいなら上のFind関数を使ってください
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

// --- 表示・アウトプット ---
// コンソールにリストを印刷する
void DoublyLinkedList::PrintForward()
{
	for (Node* cur = head; cur != &dummy; cur = cur->GetNext())
		printf("%d\t%s\n", cur->GetData().GetScore(), cur->GetData().GetName().c_str());
}
void DoublyLinkedList::PrintBackward()
{
	for (Node* cur = tail; cur != &dummy; cur = cur->GetPrev())
		printf("%d\t%s\n", cur->GetData().GetScore(), cur->GetData().GetName().c_str());
}
