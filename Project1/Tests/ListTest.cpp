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
	list.Delete(list.End().GetCurrent()->next);
	EXPECT_EQ(list.GetSize(), 1);
}

TEST(AssignmentTest, EmptyDeletion)
{
	DoublyLinkedList list;
	list.Delete(list.End());
	EXPECT_EQ(list.GetSize(), 0);
}

// --- Data Insertion ---

TEST(InsertionTest, EmptyInsertion)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	EXPECT_EQ(list.GetSize() > 0, true);
}
