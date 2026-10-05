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

TEST(ToTailTest, NoListIterate)
{
	ASSERT_DEATH(
		{
			DoublyLinkedList * list;
			list->Begin().GetNextNode();
		}, "");
	ASSERT_DEATH(
		{
			DoublyLinkedList * list;
			list->cBegin().GetNextNode();
		}, "");
}

TEST(ToTailTest, EmptyListIterate)
{
	DoublyLinkedList list;
	EXPECT_EQ(list.Begin().GetNextNode(), nullptr);
	EXPECT_EQ(list.cBegin().GetNextNode(), nullptr);
}

TEST(ToTailTest, TailIterateForward)
{
	DoublyLinkedList list;
	EXPECT_EQ(list.Last().GetCurrent()->GetNext(), nullptr);
	EXPECT_EQ(list.Last().GetCurrent()->GetNext(), nullptr);
	EXPECT_EQ(list.cLast().GetCurrent()->GetNext(), nullptr);
	EXPECT_EQ(list.cLast().GetCurrent()->GetNext(), nullptr);
}

TEST(ToTailTest, TwoElementIterateForward)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	EXPECT_EQ(list.Begin().GetNextNode()->GetData().GetName(), "pie");
	EXPECT_EQ(list.Begin().GetNextNode()->GetData().GetScore(), 1);
	EXPECT_EQ(list.cBegin().GetNextNode()->GetData().GetName(), "pie");
	EXPECT_EQ(list.cBegin().GetNextNode()->GetData().GetScore(), 1);
}

TEST(ToTailTest, PrefixIteratorIncrement)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	Iterator it = list.Begin();
	ConstIterator cit = list.cBegin();
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "cake");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "cake");
	++it;
	++cit;
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "pie");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "pie");
}

TEST(ToTailTest, PostfixIteratorIncrement)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	Iterator it = list.Begin();
	ConstIterator cit = list.cBegin();
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "cake");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "cake");
	it++;
	cit++;
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "pie");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "pie");
}

// --- Iteartor Iteration Towards Head ---

TEST(ToHeadTest, NoListIterate)
{
	ASSERT_DEATH(
		{
			DoublyLinkedList * list;
			list->End().GetPrevNode();
		}, "");
	ASSERT_DEATH(
		{
			DoublyLinkedList * list;
			list->cEnd().GetPrevNode();
		}, "");
}

TEST(ToHeadTest, EmptyListIterate)
{
	DoublyLinkedList list;
	EXPECT_EQ(list.End().GetNextNode(), nullptr);
	EXPECT_EQ(list.cEnd().GetNextNode(), nullptr);
}

TEST(ToHeadTest, TailIterateBackward)
{
	DoublyLinkedList list;
	EXPECT_EQ(list.End().GetCurrent()->GetPrev(), nullptr);
	EXPECT_EQ(list.End().GetCurrent()->GetPrev(), nullptr);
	EXPECT_EQ(list.cEnd().GetCurrent()->GetPrev(), nullptr);
	EXPECT_EQ(list.cEnd().GetCurrent()->GetPrev(), nullptr);
}

TEST(ToHeadTest, TwoElementIterateBackward)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.End(), data1);
	list.Insert(list.End(), data2);
	EXPECT_EQ(list.End().GetPrevNode()->GetData().GetName(), "cake");
	EXPECT_EQ(list.End().GetPrevNode()->GetData().GetScore(), 2);
	EXPECT_EQ(list.cEnd().GetPrevNode()->GetData().GetName(), "cake");
	EXPECT_EQ(list.cEnd().GetPrevNode()->GetData().GetScore(), 2);
}

TEST(ToHeadTest, PrefixIteratorDecrement)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.End(), data1);
	list.Insert(list.End(), data2);
	Iterator it = list.End();
	ConstIterator cit = list.cEnd();
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "");
	--it;
	--cit;
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "cake");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "cake");
}

TEST(ToHeadTest, PostfixIteratorDecrement)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.End(), data1);
	list.Insert(list.End(), data2);
	Iterator it = list.End();
	Iterator cit = list.End();
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "");
	it--;
	cit--;
	EXPECT_EQ(it.GetCurrent()->GetData().GetName(), "cake");
	EXPECT_EQ(cit.GetCurrent()->GetData().GetName(), "cake");
}

// --- Iterator Copy ---

TEST(IteratorCopy, CopyConstructor)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	Iterator it(list.Begin());
	//ConstIterator copycit(it); COMPILER ERROR AS INTENDED
	Iterator copyit(it);
	EXPECT_TRUE(it == copyit);
	it++;
	EXPECT_FALSE(it == copyit);
}

// --- Iterator to Iterator Assignment ---

TEST(IteratorToIterator, Assignment)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	ScoreData data2(2, "cake");
	list.Insert(list.Begin(), data1);
	list.Insert(list.Begin(), data2);
	Iterator it1(list.Begin());
	//ConstIterator cit = it; COMPILER ERROR AS INTENDED
	Iterator it2 = it1;
	EXPECT_TRUE(it1 == it2);
	it1++;
	EXPECT_FALSE(it1 == it2);
}

// --- Iterator Comparison - Similar ---

TEST(IteratorComparisonSimilar, EmptyHeadTail)
{
	DoublyLinkedList list;
	Iterator it1(list.Begin());
	Iterator it2(list.End());
	EXPECT_TRUE(it1 == it2);
}

TEST(IteratorComparisonSimilar, Same)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	Iterator it1(list.Begin());
	Iterator it2(list.Begin());
	EXPECT_TRUE(it1 == it2);
}

TEST(IteratorComparisonSimilar, Different)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	Iterator it1(list.Begin());
	Iterator it2(list.End());
	EXPECT_FALSE(it1 == it2);
}

// --- Iterator Comparison - Different ---

TEST(IteratorComparisonDifferent, EmptyHeadTail)
{
	DoublyLinkedList list;
	Iterator it1(list.Begin());
	Iterator it2(list.Begin());
	EXPECT_FALSE(it1 != it2);
}

TEST(IteratorComparisonDifferent, Same)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	Iterator it1(list.Begin());
	Iterator it2(list.Begin());
	EXPECT_FALSE(it1 != it2);
}

TEST(IteratorComparisonDifferent, Different)
{
	DoublyLinkedList list;
	ScoreData data1(1, "pie");
	list.Insert(list.Begin(), data1);
	Iterator it1(list.Begin());
	Iterator it2(list.End());
	EXPECT_TRUE(it1 != it2);
}