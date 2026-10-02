#include "gtest/gtest.h"
#include "pch.h"
#include "../Project1/DoublyLinkedList.h"

// --- Assignment Tests ---

TEST(AssignmentTest, EmptyList) 
{
	DoublyLinkedList list;
	int count = list.GetSize();
	EXPECT_EQ(count, 0);
}

TEST(AssignmentTest, TailInsertion)
{
	DoublyLinkedList list;
	ScoreData data(1, "pie");
	list.Insert(list.End(), data);
	EXPECT_EQ(list.GetSize(), 1);
}

TEST(AssignmentTest, TailInsertionFailure)
{
	DoublyLinkedList list;
	ScoreData badData(-150, "");
	list.Insert(list.End(), badData);
	EXPECT_EQ(list.GetSize(), 0);
}

TEST(AssignmentTest, InsertionSuccessful)
{
	DoublyLinkedList list;
	ScoreData data(1, "pie");
	list.Insert(list.Begin(), data);
	EXPECT_EQ(list.GetSize(), 1);
}

TEST(AssignmentTest, InsertionFailure)
{
	DoublyLinkedList list;
	ScoreData badData(-150, "");
	list.Insert(list.Begin(), badData);
	EXPECT_EQ(list.GetSize(), 0);
}

TEST(AssignmentTest, Delete)
{
	DoublyLinkedList list;
	ScoreData data(1, "pie");
	list.Insert(list.Begin(), data);
	list.Delete(list.Begin());
	EXPECT_EQ(list.GetSize(), 0);
}

TEST(AssignmentTest, DeletionFailure)
{
	DoublyLinkedList list;
	ScoreData data(1, "pie");
	list.Insert(list.Begin(), data);
	list.Delete(list.End());
	EXPECT_EQ(list.GetSize(), 1);
}

TEST(AssignmentTest, EmptyDeletion)
{
	DoublyLinkedList list;
	list.Delete(list.Begin());
	EXPECT_EQ(list.GetSize(), 0);
}

// --- Data Insertion ---

TEST(InsertionTest, EmptyInsertion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.End(), data1);
	EXPECT_EQ(list.GetSize() > 0, true);
}

TEST(InsertionTest, OccupiedHeadInsertion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	EXPECT_EQ(list.cBegin().GetNext()->GetName() == "pie", true);
}

TEST(InsertionTest, OccupiedTailInsertion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.End(), data1);
	list.Insert(list.End(), data2);
	EXPECT_EQ(list.cBegin().GetCurrent()->GetName() == "pie", true);
}

TEST(InsertionTest, OccupiedMidInsertion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	list.Insert(list.Begin(), data1);
	list.Insert(list.End(), data2);
	list.Insert(list.FindByName("cake"), data3);
	EXPECT_EQ(list.FindByName("macaron").GetNext()->GetName() == "cake", true);
}

TEST(InsertionTest, ConstIteratorInsertion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.cBegin(), data1);
	list.Insert(list.cBegin(), data2);
	EXPECT_EQ(list.cBegin().GetNext()->GetName() == "pie", true);
}

// --- Data Deletion ---

TEST(DeletionTest, EmptyDeletion)
{
	DoublyLinkedList list;
	list.Delete(list.Begin());
	list.Delete(list.End());
	EXPECT_EQ(list.GetSize() != 0, false);
}

TEST(DeletionTest, HeadDeletion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	list.Delete(list.Begin());
	EXPECT_EQ(list.cBegin().GetCurrent()->GetName() == "pie", true);
}

TEST(DeletionTest, TailDeletion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	list.Delete(list.End());
	EXPECT_EQ(list.GetSize() != 0, true);
}

TEST(DeletionTest, MidDeletion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	list.Insert(list.Begin(), data3);
	list.Delete(list.FindByName("pie"));
	EXPECT_EQ(list.cLast().GetCurrent()->GetName() == "cake", true);
}

TEST(DeletionTest, ConstIteratorDeletion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	list.Insert(list.Begin(), data3);
	list.Delete(list.cBegin());
	list.Delete(list.cBegin());
	EXPECT_EQ(list.cBegin().GetCurrent()->GetName() == "pie", true);
}

TEST(DeletionTest, ImproperIteratorDeletion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	list.Delete(list.cEnd());
	EXPECT_EQ(list.CheckForName("pie"), true);
}

// --- Head Iterator ---

TEST(HeadIteratorTest, EmptyList)
{
	DoublyLinkedList list;
	list.cBegin().GetCurrent();
}

TEST(HeadIteratorTest, SingleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.End(), data1);
	Iterator it = list.Begin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(HeadIteratorTest, DoubleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.End(), data1);
	list.Insert(list.End(), data2);
	Iterator it = list.Begin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(HeadIteratorTest, EntryAndCall)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	list.Insert(list.Begin(), data1);
	Iterator it = list.Begin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.End(), data2);
	it = list.Begin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.FindByName("cake"), data3);
	it = list.Begin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(HeadIteratorTest, DeleteAndCall)
{
	DoublyLinkedList list;
	// Head 4 - 3 - 2 - 1 Tail
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	ScoreData data4(4, "cookie");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	list.Insert(list.Begin(), data3);
	list.Insert(list.Begin(), data4);

	Iterator it = list.Begin();

	EXPECT_EQ((*it).score, data4.score);
	EXPECT_EQ((*it).name, data4.name);

	// Head 3 - 2 - 1 Tail
	list.Delete(list.Begin());
	it = list.Begin();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 3 - 2 Tail
	list.Delete(list.End());
	it = list.Begin();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 3 Tail
	list.Delete(list.FindByName("cake"));
	it = list.Begin();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);
}

// --- Head ConstIterator ---

TEST(HeadConstIteratorTest, EmptyList)
{
	DoublyLinkedList list;
	list.cBegin().GetCurrent();
}

TEST(HeadConstIteratorTest, SingleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.cEnd(), data1);
	ConstIterator it = list.cBegin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(HeadConstIteratorTest, DoubleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.cEnd(), data1);
	list.Insert(list.cEnd(), data2);
	ConstIterator it = list.cBegin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(HeadConstIteratorTest, EntryAndCall)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	list.Insert(list.cBegin(), data1);
	ConstIterator it = list.cBegin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.cEnd(), data2);
	it = list.cBegin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.FindByName("cake"), data3);
	it = list.cBegin();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(HeadConstIteratorTest, DeleteAndCall)
{
	DoublyLinkedList list;
	// Head 4 - 3 - 2 - 1 Tail
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	ScoreData data4(4, "cookie");
	list.Insert(list.cBegin(), data1);
	list.Insert(list.cBegin(), data2);
	list.Insert(list.cBegin(), data3);
	list.Insert(list.cBegin(), data4);

	ConstIterator it = list.cBegin();

	EXPECT_EQ((*it).score, data4.score);
	EXPECT_EQ((*it).name, data4.name);

	// Head 3 - 2 - 1 Tail
	list.Delete(list.cBegin());
	it = list.cBegin();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 3 - 2 Tail
	list.Delete(list.cEnd());
	it = list.cBegin();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 3 Tail
	list.Delete(list.FindByName("cake"));
	it = list.cBegin();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);
}

// --- End Iterator ---

TEST(EndIteratorTest, EmptyList)
{
	DoublyLinkedList list;
	list.cEnd().GetCurrent();
}

TEST(EndIteratorTest, SingleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	Iterator it = list.Last();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(EndIteratorTest, DoubleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	Iterator it = list.Last();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(EndIteratorTest, EntryAndCall)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	list.Insert(list.End(), data1);
	Iterator it = list.Last();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.Begin(), data2);
	it = list.Last();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.FindByName("cake"), data3);
	it = list.Last();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(EndIteratorTest, DeleteAndCall)
{
	DoublyLinkedList list;
	// Head 1 - 2 - 3 - 4 Tail
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	ScoreData data4(4, "cookie");
	list.Insert(list.End(), data1);
	list.Insert(list.End(), data2);
	list.Insert(list.End(), data3);
	list.Insert(list.End(), data4);

	Iterator it = list.Last();

	EXPECT_EQ((*it).score, data4.score);
	EXPECT_EQ((*it).name, data4.name);

	// Head 1 - 2 - 3 Tail
	list.Delete(list.Last());
	it = list.Last();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 2 - 3 Tail
	list.Delete(list.Begin());
	it = list.Last();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 2 Tail
	list.Delete(list.FindByName("cake"));
	it = list.Last();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);
}

// --- End ConstIterator ---

TEST(EndIteratorTest, EmptyList)
{
	DoublyLinkedList list;
	list.cEnd().GetCurrent();
}

TEST(EndIteratorTest, SingleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.cBegin(), data1);
	ConstIterator it = list.cLast();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(EndIteratorTest, DoubleEntry)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.cBegin(), data1);
	list.Insert(list.cBegin(), data2);
	ConstIterator it = list.cLast();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(EndIteratorTest, EntryAndCall)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	list.Insert(list.cEnd(), data1);
	ConstIterator it = list.cLast();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.cBegin(), data2);
	it = list.cLast();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);

	list.Insert(list.FindByName("cake"), data3);
	it = list.cLast();

	EXPECT_EQ((*it).score, data1.score);
	EXPECT_EQ((*it).name, data1.name);
}

TEST(EndIteratorTest, DeleteAndCall)
{
	DoublyLinkedList list;
	// Head 1 - 2 - 3 - 4 Tail
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	ScoreData data3(3, "macaron");
	ScoreData data4(4, "cookie");
	list.Insert(list.cEnd(), data1);
	list.Insert(list.cEnd(), data2);
	list.Insert(list.cEnd(), data3);
	list.Insert(list.cEnd(), data4);

	ConstIterator it = list.cLast();

	EXPECT_EQ((*it).score, data4.score);
	EXPECT_EQ((*it).name, data4.name);

	// Head 1 - 2 - 3 Tail
	list.Delete(list.cLast());
	it = list.cLast();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 2 - 3 Tail
	list.Delete(list.cBegin());
	it = list.cLast();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);

	// Head 2 Tail
	list.Delete(list.FindByName("cake"));
	it = list.cLast();

	EXPECT_EQ((*it).score, data3.score);
	EXPECT_EQ((*it).name, data3.name);
}