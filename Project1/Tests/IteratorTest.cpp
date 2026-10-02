#include "gtest/gtest.h"
#include "pch.h"
#include "../Project1/DoublyLinkedList.h"

// --- Iterator Retrieval ---

TEST(RetrievalTest, NoList)
{
	ASSERT_DEATH(
		{
			DoublyLinkedList * list;
			list->Begin();
		}, "");

	ASSERT_DEATH(
		{
			DoublyLinkedList* list;
			list->cBegin();
		}, "");	
}

TEST(RetrievalTest, IteratorValueAssignment)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	list.Begin().GetCurrent()->GetData().WriteName("ARAGHAO");
	EXPECT_TRUE(list.Begin().GetCurrent()->GetData().GetName() != data1.GetName());
}

TEST(RetrievalTest, EmptyList)
{
	DoublyLinkedList list;
	ASSERT_EQ(list.Begin(), list.End());
	ASSERT_EQ(list.cBegin(), list.cEnd());
}

TEST(RetrievalTest, EndCall)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	ASSERT_EQ(list.cEnd().GetCurrent()->GetData().GetScore(), 0);
	ASSERT_EQ(list.cEnd().GetCurrent()->GetData().GetName(), "");
	ASSERT_EQ(list.cEnd().GetCurrent()->GetNext(), nullptr);
	ASSERT_TRUE(list.cEnd().GetCurrent()->GetPrev() != nullptr);
}

// --- Iterator Iteration Towards Tail ---