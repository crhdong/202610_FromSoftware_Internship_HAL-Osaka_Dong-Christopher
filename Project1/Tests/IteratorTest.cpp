#include "gtest/gtest.h"
#include "pch.h"
#include "../Project1/DoublyLinkedList.h"

namespace IteratorTests
{
	// --------------------
	// --- イテレータ取得 ---
	// --------------------

	// イテレータが参照がない
	// EXPECT NE
	// EXPECT SIZE0 
	TEST(RetrievalTest, 0_UnreferencedIterator)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		DoublyLinkedList<ScoreData>::Iterator it(nullptr, nullptr);

		list.Insert(it, data1);

		EXPECT_NE(list.Begin(), it);
		EXPECT_NE(list.cBegin(), it);
		EXPECT_EQ(list.GetSize(), 0);

		list.Insert(list.Begin(), data1);

		EXPECT_NE(list.Begin(), it);
		EXPECT_NE(list.cBegin(), it);
	}

	// イテレータでデータを取得して、上書き
	TEST(RetrievalTest, 1_IteratorValueAssignment)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		(*list.Begin()).WriteName("ARAGHAO");
		EXPECT_TRUE((*list.Begin()).GetName() == "ARAGHAO");
	}

	// 空きリスト取得
	// 先頭 == 末尾
	TEST(RetrievalTest, 3_EmptyList)
	{
		DoublyLinkedList<ScoreData> list;
		ASSERT_EQ(list.Begin(), list.End());
		ASSERT_EQ(list.cBegin(), list.cEnd());
	}

	// Endでdummyノードを取得
	TEST(RetrievalTest, 4_EndCall)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		EXPECT_EQ((*++list.cLast()).GetScore(), -1);
		EXPECT_EQ((*++list.cLast()).GetName(), "");
	}

	// -----------------------
	// --- 末尾向けイテレータ ---
	// -----------------------

	// イテレータの参照がない++
	// EXPECT SAME
	// EXPECT NE
	TEST(ToTailTest, 5_UnreferencedIteratorForward)
	{
		DoublyLinkedList<ScoreData> list;
		DoublyLinkedList<ScoreData>::Iterator it(nullptr, nullptr);
		DoublyLinkedList<ScoreData>::Iterator it2(nullptr, nullptr);

		EXPECT_EQ(it, ++it);
		EXPECT_EQ(it, it2);
		EXPECT_NE(it, list.Begin());
		EXPECT_NE(it, list.End());
		EXPECT_NE(it, list.cBegin());
		EXPECT_NE(it, list.cEnd());
	}

	// 空きリストの先頭から末尾に移動
	// dummy
	TEST(ToTailTest, 6_EmptyListIterate)
	{
		DoublyLinkedList<ScoreData> list;
		EXPECT_EQ(++list.Begin(), list.End());
		EXPECT_EQ(++list.cBegin(), list.cEnd());
	}

	// 空きリストの末尾から末尾+1に移動
	// dummy
	TEST(ToTailTest, 7_TailIterateForward)
	{
		DoublyLinkedList<ScoreData> list;
		EXPECT_EQ(++list.End(), list.End());
		EXPECT_EQ(++list.cEnd(), list.cEnd());
	}

	// 二つ以上なリストの先頭から末尾に移動
	// 第二のノードを返す
	TEST(ToTailTest, 8_TwoElementIterateForward)
	{
		DoublyLinkedList<ScoreData> list;
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
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList<ScoreData>::Iterator it = list.Begin();
		DoublyLinkedList<ScoreData>::ConstIterator cit = list.cBegin();
		DoublyLinkedList<ScoreData>::Iterator it2 = it;
		DoublyLinkedList<ScoreData>::ConstIterator cit2 = cit;
		EXPECT_FALSE(it == ++it2);
		EXPECT_FALSE(cit == ++cit2);
		EXPECT_EQ((*it2).GetName(), "pie");
		EXPECT_EQ((*cit2).GetName(), "pie");
	}

	// ++operator(int)テスト
	TEST(ToTailTest, 10_PostfixIteratorIncrement)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList<ScoreData>::Iterator it = list.Begin();
		DoublyLinkedList<ScoreData>::ConstIterator cit = list.cBegin();
		DoublyLinkedList<ScoreData>::Iterator it2 = it;
		DoublyLinkedList<ScoreData>::ConstIterator cit2 = cit;
		EXPECT_TRUE(it2 == it++);
		EXPECT_TRUE(cit2 == cit++);
		EXPECT_EQ((*it).GetName(), "pie");
		EXPECT_EQ((*cit).GetName(), "pie");
	}

	// -----------------------
	// --- 先頭向けイテレータ ---
	// -----------------------

	// イテレータの参照がない--
	// EXPECT SAME
	// EXPECT NE
	TEST(ToHeadTest, 11_UnreferencedIteratorForward)
	{
		DoublyLinkedList<ScoreData> list;
		DoublyLinkedList<ScoreData>::Iterator it(nullptr, nullptr);
		DoublyLinkedList<ScoreData>::Iterator it2(nullptr, nullptr);

		EXPECT_EQ(it, --it);
		EXPECT_EQ(it, it2);
		EXPECT_NE(it, list.Begin());
		EXPECT_NE(it, list.End());
		EXPECT_NE(it, list.cBegin());
		EXPECT_NE(it, list.cEnd());
	}

	// 空きリストの末尾から先頭に移動
	// dummy
	TEST(ToHeadTest, 12_EmptyList)
	{
		DoublyLinkedList<ScoreData> list;
		EXPECT_EQ((*list.Last()).GetName(), "");
		EXPECT_EQ((*list.cLast()).GetName(), "");
	}

	// 空きリストの末尾+1から末尾に移動
	// まだdummy
	TEST(ToHeadTest, 13_TailIterateBackward)
	{
		DoublyLinkedList<ScoreData> list;
		EXPECT_EQ((*list.Begin()).GetName(), "");
		EXPECT_EQ((*list.cBegin()).GetName(), "");
	}

	// 二つ以上なリストのEndから先頭に移動
	// dummyじゃない
	TEST(ToHeadTest, 14_TwoElementIterateBackward)
	{
		DoublyLinkedList<ScoreData> list;
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
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		DoublyLinkedList<ScoreData>::Iterator it = list.End();
		DoublyLinkedList<ScoreData>::ConstIterator cit = list.cEnd();
		DoublyLinkedList<ScoreData>::Iterator it2 = it;
		DoublyLinkedList<ScoreData>::ConstIterator cit2 = cit;
		EXPECT_FALSE(--it == it2);
		EXPECT_FALSE(--cit == cit2);
		EXPECT_EQ((*it).GetName(), "cake");
		EXPECT_EQ((*cit).GetName(), "cake");
	}

	// --operator(int)
	TEST(ToHeadTest, 16_PostfixIteratorDecrement)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		DoublyLinkedList<ScoreData>::Iterator it = list.End();
		DoublyLinkedList<ScoreData>::ConstIterator cit = list.cEnd();
		DoublyLinkedList<ScoreData>::Iterator it2 = it;
		DoublyLinkedList<ScoreData>::ConstIterator cit2 = cit;
		EXPECT_TRUE(it2 == it--);
		EXPECT_TRUE(cit2 == cit--);
		EXPECT_EQ((*it).GetName(), "cake");
		EXPECT_EQ((*cit).GetName(), "cake");
	}

	// --- イテレータのコピーコンストラクタ ---

	TEST(IteratorCopy, 18_CopyConstructor)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList<ScoreData>::Iterator it(list.Begin());
		//ConstIterator copycit(it); COMPILER ERROR AS INTENDED
		DoublyLinkedList<ScoreData>::Iterator copyit(it);
		EXPECT_TRUE(it == copyit);
		it++;
		EXPECT_FALSE(it == copyit);
	}

	// --- イテレータをイテレータに代入 ---

	TEST(IteratorToIterator, 20_Assignment)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList<ScoreData>::Iterator it1(list.Begin());
		//ConstIterator cit = it; COMPILER ERROR AS INTENDED
		DoublyLinkedList<ScoreData>::Iterator it2 = it1;
		EXPECT_TRUE(it1 == it2);
		it1++;
		EXPECT_FALSE(it1 == it2);
	}

	// --------------------
	// --- イテレータ == ---
	// --------------------

	// 空きリスト
	// true
	TEST(IteratorComparisonSimilar, 21_EmptyHeadTail)
	{
		DoublyLinkedList<ScoreData> list;
		DoublyLinkedList<ScoreData>::Iterator it1(list.Begin());
		DoublyLinkedList<ScoreData>::Iterator it2(list.End());
		EXPECT_TRUE(it1 == it2);
	}

	// 実に同じ
	// true
	TEST(IteratorComparisonSimilar, 22_Same)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList<ScoreData>::Iterator it1(list.Begin());
		DoublyLinkedList<ScoreData>::Iterator it2(list.Begin());
		EXPECT_TRUE(it1 == it2);
	}

	// 実に違う
	// false
	TEST(IteratorComparisonSimilar, 23_Different)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList<ScoreData>::Iterator it1(list.Begin());
		DoublyLinkedList<ScoreData>::Iterator it2(list.End());
		EXPECT_FALSE(it1 == it2);
	}

	// --------------------
	// --- イテレータ != ---
	// --------------------
	
	// 空きリスト
	// false
	TEST(IteratorComparisonDifferent, 24_EmptyHeadTail)
	{
		DoublyLinkedList<ScoreData> list;
		DoublyLinkedList<ScoreData>::Iterator it1(list.Begin());
		DoublyLinkedList<ScoreData>::Iterator it2(list.Begin());
		EXPECT_FALSE(it1 != it2);
	}
	// 実に同じ
	// false
	TEST(IteratorComparisonDifferent, 25_Same)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList<ScoreData>::Iterator it1(list.Begin());
		DoublyLinkedList<ScoreData>::Iterator it2(list.Begin());
		EXPECT_FALSE(it1 != it2);
	}
	// 実に違う
	// true
	TEST(IteratorComparisonDifferent, 26_Different)
	{
		DoublyLinkedList<ScoreData> list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList<ScoreData>::Iterator it1(list.Begin());
		DoublyLinkedList<ScoreData>::Iterator it2(list.End());
		EXPECT_TRUE(it1 != it2);
	}
}