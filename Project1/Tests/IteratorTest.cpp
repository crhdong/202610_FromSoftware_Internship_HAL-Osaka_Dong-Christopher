#include "gtest/gtest.h"
#include "pch.h"
#include "../Project1/DoublyLinkedList.h"

namespace IteratorTests
{
	// -------------------- //
	// --- イテレータ取得 --- //
	// -------------------- //

	// リストが存在しない（死ぬ）
	// ASSERT DEATH (エラーボックス２個）
	TEST(RetrievalTest, 0_NoList)
	{
		ASSERT_DEATH(
			{
				DoublyLinkedList* list;
				list->Begin();
			}, "");

		ASSERT_DEATH(
			{
				DoublyLinkedList* list;
				list->cBegin();
			}, "");
	}

	// イテレータでデータを取得して、上書き
	// EXPECT TRUE (新しいstring）
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
	// EXPECT HEAD == TAIL
	TEST(RetrievalTest, 3_EmptyList)
	{
		DoublyLinkedList list;
		ASSERT_EQ(list.Begin(), list.End());
		ASSERT_EQ(list.cBegin(), list.cEnd());
	}

	// Endでdummyノードを取得
	// EXPECT DUMMY
	TEST(RetrievalTest, 4_EndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		ASSERT_EQ((*list.cEnd()).GetScore(), 0);
		ASSERT_EQ((*list.cEnd()).GetName(), "");
	}

	// ----------------------- //
	// --- 末尾向けイテレータ --- //
	// ----------------------- //

	// リストが存在しないでも ++（死ぬ）
	// ASSERT DEATH
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
	// ++先頭 == 末尾
	// EXPECT ++HEAD == TAIL
	TEST(ToTailTest, 6_EmptyListIterate)
	{
		DoublyLinkedList list;
		EXPECT_EQ(++list.Begin(), list.End());
		EXPECT_EQ(++list.cBegin(), list.cEnd());
	}

	// 空きリストの末尾から末尾+1に移動
	// ++末尾 == 末尾
	// EXPECT ++TAIL == TAIL
	TEST(ToTailTest, 7_TailIterateForward)
	{
		DoublyLinkedList list;
		EXPECT_EQ(++list.End(), list.End());
		EXPECT_EQ(++list.cEnd(), list.cEnd());
	}

	// 二つ以上のリストを後ろ向きにイテレータを呼ぶ
	// 順番とイテレータ確認
	// EXPECT data2 THEN data1
	TEST(ToTailTest, 8_TwoElementIterateForward)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList::Iterator it = list.Begin();

		EXPECT_EQ((*it).GetName(), data2.GetName());
		EXPECT_EQ((*it).GetScore(), data2.GetScore());
		
		++it;

		EXPECT_EQ((*it).GetName(), data1.GetName());
		EXPECT_EQ((*it).GetScore(), data1.GetScore());
	}

	// ++operatorテスト
	// ノードの両面も確認
	// ++は 増加ー＞return 
	TEST(ToTailTest, 9_PrefixIteratorIncrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		list.Insert(list.cBegin(), data2);
		list.Insert(list.Begin(), data3);
		DoublyLinkedList::Iterator it = list.Begin();
		DoublyLinkedList::ConstIterator cit = list.cBegin();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_FALSE(it == ++it2);
		EXPECT_FALSE(cit == ++cit2);
		EXPECT_TRUE((*it).GetName() == data3.GetName());
		EXPECT_TRUE((*cit).GetName() == data3.GetName());
		EXPECT_TRUE((*it2).GetName() == data2.GetName());
		EXPECT_TRUE((*cit2).GetName() == data2.GetName());
		EXPECT_TRUE((*(++it2)).GetName() == data1.GetName());
		EXPECT_TRUE((*(++cit2)).GetName() == data1.GetName());
	}

	// ++operator(int)テスト
	// ノードの両面も確認
	// ++(int)は return ー＞ 増加
	TEST(ToTailTest, 10_PostfixIteratorIncrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		list.Insert(list.Begin(), data3);
		DoublyLinkedList::Iterator it = list.Begin();
		DoublyLinkedList::ConstIterator cit = list.cBegin();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_TRUE(it == it2++);
		EXPECT_TRUE(cit == cit2++);
		EXPECT_TRUE((*it).GetName() == data3.GetName());
		EXPECT_TRUE((*cit).GetName() == data3.GetName());
		EXPECT_TRUE((*it2++).GetName() == data2.GetName());
		EXPECT_TRUE((*cit2++).GetName() == data2.GetName());
		EXPECT_TRUE((*it2).GetName() == data1.GetName());
		EXPECT_TRUE((*cit2).GetName() == data1.GetName());
	}

	// ----------------------- //
	// --- 先頭向けイテレータ --- //
	// ----------------------- //

	// リストが存在しない（死ぬ）
	// ASSERT DEATH (エラーボックス２個）
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
	// --末尾 == 先頭
	// EXPECT ++TAIL == HEAD
	TEST(ToHeadTest, 12_EmptyList)
	{
		DoublyLinkedList list;
		EXPECT_EQ(--list.Last(), list.Begin());
		EXPECT_EQ(--list.cLast(), list.cBegin());
	}

	// 空きリストの先頭から先頭-1に移動
	// --先頭 == 先頭
	// EXPECT --HEAD == HEAD
	TEST(ToHeadTest, 13_HeadIterateBackward)
	{
		DoublyLinkedList list;
		EXPECT_EQ(--list.Begin(), list.Begin());
		EXPECT_EQ(--list.cBegin(), list.cBegin());
	}

	// 二つ以上のリストを前向きにイテレータを呼ぶ
	// 順番とイテレータ確認
	// EXPECT data1 THEN data2
	TEST(ToHeadTest, 14_TwoElementIterateBackward)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList::Iterator it = list.Last();

		EXPECT_EQ((*it).GetName(), data1.GetName());
		EXPECT_EQ((*it).GetScore(), data1.GetScore());

		--it;

		EXPECT_EQ((*it).GetName(), data2.GetName());
		EXPECT_EQ((*it).GetScore(), data2.GetScore());
	}

	// --operatorテスト
	// ノードの両面も確認
	// --は 減少ー＞return 
	TEST(ToHeadTest, 15_PrefixIteratorDecrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		list.Insert(list.End(), data3);
		DoublyLinkedList::Iterator it = list.Last();
		DoublyLinkedList::ConstIterator cit = list.cLast();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_FALSE(it == --it2);
		EXPECT_FALSE(cit == --cit2);
		EXPECT_TRUE((*it).GetName() == data3.GetName());
		EXPECT_TRUE((*cit).GetName() == data3.GetName());
		EXPECT_TRUE((*it2).GetName() == data2.GetName());
		EXPECT_TRUE((*cit2).GetName() == data2.GetName());
		EXPECT_TRUE((*(--it2)).GetName() == data1.GetName());
		EXPECT_TRUE((*(--cit2)).GetName() == data1.GetName());
	}

	// --operator(int)テスト
	// ノードの両面も確認
	// --(int)は return ー＞ 減少
	TEST(ToHeadTest, 16_PostfixIteratorDecrement)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		list.Insert(list.End(), data3);
		DoublyLinkedList::Iterator it = list.Last();
		DoublyLinkedList::ConstIterator cit = list.cLast();
		DoublyLinkedList::Iterator it2 = it;
		DoublyLinkedList::ConstIterator cit2 = cit;
		EXPECT_EQ(it--, it2);
		EXPECT_EQ(cit--, cit2);
		EXPECT_EQ((*it2).GetName(), "macaron");
		EXPECT_EQ((*cit2).GetName(), "macaron");
		EXPECT_EQ((*it--).GetName(), "cake");
		EXPECT_EQ((*cit--).GetName(), "cake");
		EXPECT_EQ((*it).GetName(), "pie");
		EXPECT_EQ((*cit).GetName(), "pie");
	}

	// ----------------------------------- //
	// --- イテレータのコピーコンストラクタ --- //
	// ----------------------------------- //

	// コピーイテレータをチェック
	// 先ずコピーをチェック、次コピーの++もチェック
	// EXPECT TRUE THEN FALSE
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

	// -------------------------------- //
	// --- イテレータをイテレータに代入 --- //
	// -------------------------------- //

	// operator=
	// イテレータを他のイテレータに代入チェック
	// 先ず代入をチェック、次代入したの++もチェック
	// EXPECT TRUE THEN FALSE
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

	// ------------------- //
	// --- イテレータ == --- //
	// ------------------- //

	// 空きリスト先頭と末尾を比べ
	// EXPECT TRUE
	TEST(IteratorComparisonSimilar, 21_EmptyHeadTail)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.End());
		EXPECT_TRUE(it1 == it2);
	}

	// 同じ一位のイテレータ
	// EXPECT TRUE
	TEST(IteratorComparisonSimilar, 22_Same)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.Begin());
		EXPECT_TRUE(it1 == it2);
	}

	// 別一位のイテレータ
	// EXPECT FALSE
	TEST(IteratorComparisonSimilar, 23_Different)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.End());
		EXPECT_FALSE(it1 == it2);
	}

	// ------------------- //
	// --- イテレータ != --- //
	// ------------------- //
	
	// 空きリスト先頭と末尾を比べ
	// EXPECT FALSE
	TEST(IteratorComparisonDifferent, 24_EmptyHeadTail)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.Begin());
		EXPECT_FALSE(it1 != it2);
	}

	// 同じ一位のイテレータ
	// EXPECT FALSE
	TEST(IteratorComparisonDifferent, 25_Same)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it1(list.Begin());
		DoublyLinkedList::Iterator it2(list.Begin());
		EXPECT_FALSE(it1 != it2);
	}

	// 別一位のイテレータ
	// EXPECT TRUE
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