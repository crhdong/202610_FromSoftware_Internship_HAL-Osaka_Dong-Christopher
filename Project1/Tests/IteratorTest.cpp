#include "gtest/gtest.h"
#include "pch.h"
#include "../Project1/DoublyLinkedList.h"

namespace IteratorTests
{

	// --- イテレータ取得 ---

	// リストが存在しない（死ぬ）
	TEST(RetrievalTest, 0_NoList)
	{
		ASSERT_DEATH(
			{
				DoublyLinkedList * list;
				list->Begin();
			}, "");

		ASSERT_DEATH(
			{
				DoublyLinkedList * list;
				list->cBegin();
			}, "");
	}

	// イテレータでデータを取得して、上書き
	TEST(RetrievalTest, 1_IteratorValueAssignment)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		(*list.Begin()).WriteName("ARAGHAO");
		EXPECT_TRUE((*list.Begin()).GetName() == "ARAGHAO");
	}

	// 空きリスト取得
	// 先頭 == 末尾
	TEST(RetrievalTest, 3_EmptyList)
	{
		DoublyLinkedList list;
		ASSERT_EQ(list.Begin(), list.End());
		ASSERT_EQ(list.cBegin(), list.cEnd());
	}

	// Endでdummyノードを取得
	TEST(RetrievalTest, 4_EndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		ASSERT_EQ((*list.cEnd()).GetScore(), 0);
		ASSERT_EQ((*list.cEnd()).GetName(), "");
		ASSERT_EQ(++list.cEnd(), nullptr);
		ASSERT_TRUE(--list.cEnd() != nullptr);
	}

	// --- 末尾向けイテレータ ---

	// リストが存在しない（死ぬ）
	TEST(ToTailTest, 5_NoListIterate)
	{
		ASSERT_DEATH(
			{
				DoublyLinkedList * list;
				++list->Begin();
			}, "");
		ASSERT_DEATH(
			{
				DoublyLinkedList * list;
				++list->cBegin();
			}, "");
	}

	// 空きリストの先頭から末尾に移動
	// dummy
	TEST(ToTailTest, 6_EmptyListIterate)
	{
		DoublyLinkedList list;
		EXPECT_EQ(++list.Begin(), nullptr);
		EXPECT_EQ(++list.cBegin(), nullptr);
	}

	// 空きリストの末尾から末尾+1に移動
	// dummy
	TEST(ToTailTest, 7_TailIterateForward)
	{
		DoublyLinkedList list;
		EXPECT_EQ(++list.Last(), nullptr);
		EXPECT_EQ(++list.cLast(), nullptr);
	}

	// 二つ以上なリストの先頭から末尾に移動
	// 第二のノードを返す
	TEST(ToTailTest, 8_TwoElementIterateForward)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		EXPECT_EQ((*list.Begin()).GetName(), "cake");
		EXPECT_EQ((*list.Begin()).GetScore(), 2);
		EXPECT_EQ((*list.cBegin()).GetName(), "cake");
		EXPECT_EQ((*list.cBegin()).GetScore(), 2);
	}

	// ++operatorテスト
	TEST(ToTailTest, 9_PrefixIteratorIncrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList::Iterator it = list.Begin();
		DoublyLinkedList::ConstIterator cit = list.cBegin();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_FALSE(it == ++it2);
		EXPECT_FALSE(cit == ++cit2);
		EXPECT_EQ((*it2).GetName(), "pie");
		EXPECT_EQ((*cit2).GetName(), "pie");
	}

	// ++operator(int)テスト
	TEST(ToTailTest, 10_PostfixIteratorIncrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList::Iterator it = list.Begin();
		DoublyLinkedList::ConstIterator cit = list.cBegin();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_EQ(it2, it++);
		EXPECT_EQ(cit2, cit++);
		EXPECT_EQ((*it).GetName(), "pie");
		EXPECT_EQ((*cit).GetName(), "pie");
	}

	// --- 先頭向けイテレータ ---

	// リストが存在しない（死ぬ）
	TEST(ToHeadTest, 11_NoListIterate)
	{
		ASSERT_DEATH(
			{
				DoublyLinkedList * list;
				--list->End();
			}, "");
		ASSERT_DEATH(
			{
				DoublyLinkedList * list;
				--list->cEnd();
			}, "");
	}

	// 空きリストの末尾から先頭に移動
	// dummy
	TEST(ToHeadTest, 12_EmptyListIterate)
	{
		DoublyLinkedList list;
		EXPECT_EQ(++list.End(), nullptr);
		EXPECT_EQ(++list.cEnd(), nullptr);
	}

	// 空きリストの末尾+1から末尾に移動
	// まだdummy
	TEST(ToHeadTest, 13_TailIterateBackward)
	{
		DoublyLinkedList list;
		EXPECT_EQ(--list.End(), nullptr);
		EXPECT_EQ(--list.cEnd(), nullptr);
	}

	// 二つ以上なリストのEndから先頭に移動
	// dummyじゃない
	TEST(ToHeadTest, 14_TwoElementIterateBackward)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		EXPECT_EQ((*list.Last()).GetName(), "cake");
		EXPECT_EQ((*list.Last()).GetScore(), 2);
		EXPECT_EQ((*list.cLast()).GetName(), "cake");
		EXPECT_EQ((*list.cLast()).GetScore(), 2);
	}

	// --operator
	TEST(ToHeadTest, 15_PrefixIteratorDecrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		DoublyLinkedList::Iterator it = list.End();
		DoublyLinkedList::ConstIterator cit = list.cEnd();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_FALSE(--it == it2);
		EXPECT_FALSE(--cit == cit2);
		EXPECT_EQ((*it).GetName(), "cake");
		EXPECT_EQ((*cit).GetName(), "cake");
	}

	// --operator(int)
	TEST(ToHeadTest, 16_PostfixIteratorDecrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		DoublyLinkedList::Iterator it = list.End();
		DoublyLinkedList::ConstIterator cit = list.cEnd();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_EQ(it2, it--);
		EXPECT_EQ(cit2, cit--);
		EXPECT_EQ((*it).GetName(), "cake");
		EXPECT_EQ((*cit).GetName(), "cake");
	}

	// --- イテレータのコピーコンストラクタ ---

	TEST(IteratorCopy, 18_CopyConstructor)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList::Iterator it(list.Begin());
		//ConstIterator copycit(it); COMPILER ERROR AS INTENDED
		DoublyLinkedList::Iterator copyit(it);
		EXPECT_TRUE(it == copyit);
		it++;
		EXPECT_FALSE(it == copyit);
	}

	// --- イテレータをイテレータに代入 ---

	TEST(IteratorToIterator, 20_Assignment)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList::Iterator it1(list.Begin());
		//ConstIterator cit = it; COMPILER ERROR AS INTENDED
		DoublyLinkedList::Iterator it2 = it1;
		EXPECT_TRUE(it1 == it2);
		it1++;
		EXPECT_FALSE(it1 == it2);
	}

	// --- イテレータ == ---

	// 空きリスト
	// true
	TEST(IteratorComparisonSimilar, 21_EmptyHeadTail)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.End());
		EXPECT_TRUE(it1 == it2);
	}

	// 実に同じ
	// true
	TEST(IteratorComparisonSimilar, 22_Same)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.Begin());
		EXPECT_TRUE(it1 == it2);
	}

	// 実に違う
	// false
	TEST(IteratorComparisonSimilar, 23_Different)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.End());
		EXPECT_FALSE(it1 == it2);
	}

	// --- イテレータ != ---
	
	// 空きリスト
	// false
	TEST(IteratorComparisonDifferent, 24_EmptyHeadTail)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.Begin());
		EXPECT_FALSE(it1 != it2);
	}
	// 実に同じ
	// false
	TEST(IteratorComparisonDifferent, 25_Same)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.Begin());
		EXPECT_FALSE(it1 != it2);
	}
	// 実に違う
	// true
	TEST(IteratorComparisonDifferent, 26_Different)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.End());
		EXPECT_TRUE(it1 != it2);
	}
}