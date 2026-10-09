#include "gtest/gtest.h"
#include "pch.h"
#include "../Project1/DoublyLinkedList.h"

namespace ListTests
{
	// ---------------------- //
	// --- 挿入・解除テスト --- //
	// ---------------------- //

	// 空きリストサイズ
	// EXPECT 0
	TEST(AssignmentTest, 0_EmptyList)
	{
		DoublyLinkedList list;
		EXPECT_EQ(list.GetSize(), 0);
	}

	// 末尾で挿入
	// EXPECT 1
	TEST(AssignmentTest, 1_TailInsertion)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		list.Insert(list.End(), data);
		EXPECT_EQ(list.GetSize(), 1);
	}

	// 末尾で挿入失敗
	// EXPECT 0
	TEST(AssignmentTest, 2_TailInsertionFailure)
	{
		DoublyLinkedList list;
		DoublyLinkedList otherList;
		ScoreData data(1, "pie");
		list.Insert(otherList.End(), data);
		EXPECT_EQ(list.GetSize(), 0);
	}

	// 先頭で挿入成功
	// EXPECT 1
	TEST(AssignmentTest, 3_InsertionSuccessful)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		list.Insert(list.Begin(), data);
		EXPECT_EQ(list.GetSize(), 1);
	}

	// 先頭で挿入失敗
	// EXPECT 0
	TEST(AssignmentTest, 4_InsertionFailure)
	{
		DoublyLinkedList list;
		DoublyLinkedList otherList;
		ScoreData data(1, "pie");
		list.Insert(otherList.Begin(), data);
		EXPECT_EQ(list.GetSize(), 0);
	}

	// ノードを解除
	// EXPECT 0
	TEST(AssignmentTest, 5_Delete)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		list.Insert(list.Begin(), data);
		list.Delete(list.Begin());
		EXPECT_EQ(list.GetSize(), 0);
	}

	// 末尾+1を解除（失敗）
	// EXPECT 1
	TEST(AssignmentTest, 6_DeletionFailure)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		DoublyLinkedList::Iterator bad(nullptr, nullptr);
		list.Insert(list.Begin(), data);
		list.Delete(list.End());
		list.Delete(bad);
		EXPECT_EQ(list.GetSize(), 1);
	}

	// 何もところを解除（影響がない)
	// EXPECT 0
	TEST(AssignmentTest, 7_EmptyDeletion)
	{
		DoublyLinkedList list;
		list.Delete(list.Begin());
		list.Delete(list.cBegin());
		EXPECT_EQ(list.GetSize(), 0);
	}

	// ----------------- //
	// --- 挿入テスト --- //
	// ----------------- //

	// 空きリスト挿入
	// EXPECT TRUE
	TEST(InsertionTest, 9_EmptyInsertion)
	{
		DoublyLinkedList list1;
		DoublyLinkedList list2;
		DoublyLinkedList list3;
		ScoreData data1(1, "pie");
		EXPECT_TRUE(list1.Insert(list1.Begin(), data1));
		EXPECT_TRUE(list2.Insert(list2.Last(), data1));
		EXPECT_TRUE(list3.Insert(list3.End(), data1));
	}

	// ノードがあるリストに先頭で挿入
	// 前の先頭が+1に移動する
	// EXPECT TRUE
	TEST(InsertionTest, 10_OccupiedHeadInsertion)
	{
		DoublyLinkedList list1;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list1.Insert(list1.Begin(), data1);
		list1.Insert(list1.Begin(), data2);
		EXPECT_EQ((*list1.Begin()).GetName(), data2.GetName());
	}

	// ノードがあるリストに末尾で挿入
	// LastよりEndを使って、新しい末尾（前の末尾に+1）になる
	// EXPECT TRUE
	TEST(InsertionTest, 11_OccupiedTailInsertion)
	{
		DoublyLinkedList list1;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list1.Insert(list1.End(), data1);
		list1.Insert(list1.End(), data2);
		EXPECT_EQ((*list1.cBegin()).GetName(), data1.GetName());
	}

	// ノードがあるリストの中で挿入
	// EXPECT TRUE
	TEST(InsertionTest, 12_OccupiedMidInsertion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		list.Insert(list.End(), data2);
		list.Insert(list.Last(), data3);
		DoublyLinkedList::Iterator it1 = list.FindByName("macaron");
		DoublyLinkedList::Iterator it2 = it1;
		EXPECT_EQ((*it1).GetName(), data3.GetName());
		++it1;
		--it2;
		EXPECT_EQ((*it1).GetName(), data2.GetName());
		EXPECT_EQ((*it2).GetName(), data1.GetName());
	}

	// コンストイテレータで挿入
	// EXPECT TRUE
	TEST(InsertionTest, 13_ConstIteratorInsertion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		EXPECT_TRUE(list.Insert(list.cBegin(), data1));
		EXPECT_TRUE(list.Insert(list.cEnd(), data2));
		EXPECT_TRUE(list.Insert(list.cLast(), data3));
		DoublyLinkedList::Iterator it1 = list.FindByScore(3);
		DoublyLinkedList::Iterator it2 = it1;
		EXPECT_EQ((*it1).GetName(), "macaron");
		++it1;
		--it2;
		EXPECT_EQ((*it1).GetName(), "cake");
		EXPECT_EQ((*it2).GetName(), "pie");
	}

	// 不正イテレータで挿入
	// EXPECT FALSE
	TEST(InsertionTest, 14_InvalidIteratorInsertion)
	{
		DoublyLinkedList list;
		DoublyLinkedList otherlist;
		ScoreData data1(1, "pie");
		EXPECT_FALSE(list.Insert(otherlist.Begin(), data1));
		EXPECT_EQ(list.GetSize(), 0);
	}

	// ----------------- //
	// --- データ解除 --- //
	// ----------------- //

	// 何もないところを解除
	// EXPECT FALSE
	TEST(DeletionTest, 16_EmptyDeletion)
	{
		DoublyLinkedList list;
		EXPECT_FALSE(list.Delete(list.Begin()));
		EXPECT_FALSE(list.Delete(list.Last()));
		EXPECT_FALSE(list.Delete(list.End()));
	}

	// ノード二つ以上リストの先頭を解除
	// 先頭が変える
	// EXPECT TRUE
	TEST(DeletionTest, 17_HeadDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		EXPECT_TRUE(list.Delete(list.Begin()));
	}

	// ノード二つ以上リストの末尾を解除
	// 末尾が変える
	// EXPECT FALSE
	TEST(DeletionTest, 18_TailDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);		
		list.Insert(list.Begin(), data2);		
		EXPECT_FALSE(list.Delete(list.End()));
	}

	// ノードが三つ以上リストの真中を解除
	// 先頭と末尾が変えないがサイズが変わる
	// EXPECT TRUE
	TEST(DeletionTest, 19_MidDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		list.Insert(list.Begin(), data3);
		int size = list.GetSize();
		EXPECT_TRUE(list.Delete(list.FindByName("cake")));
		EXPECT_EQ((*list.Last()).GetName(), data1.GetName());
		EXPECT_EQ((*list.Begin()).GetName(), data3.GetName());
		EXPECT_EQ(list.GetSize(), --size);
	}

	// コンストイテレータで解除
	// EXPECT TRUE
	TEST(DeletionTest, 20_ConstIteratorDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		list.Insert(list.Begin(), data3);
		int size = list.GetSize();
		EXPECT_TRUE(list.Delete(--list.cLast()));
		EXPECT_EQ((*list.Last()).GetName(), data1.GetName());
		EXPECT_EQ((*list.Begin()).GetName(), data3.GetName());
		EXPECT_EQ(list.GetSize(), --size);
	}

	// 不正なイテレータで解除
	// EXPECT FALSE
	TEST(DeletionTest, 21_ImproperIteratorDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		DoublyLinkedList::Iterator it(nullptr, nullptr);
		list.Insert(list.Begin(), data1);
		EXPECT_FALSE(list.Delete(list.cEnd()));
		EXPECT_FALSE(list.Delete(it));
	}
	 
	// -------------------- //
	// --- 先頭イテレータ --- //
	// -------------------- //

	// 空きリストの先頭イテレータ
	// EXPECT DUMMY
	TEST(HeadIteratorTest, 23_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it = list.Begin();
		ScoreData dummy(0, "");

		EXPECT_EQ((*it).GetScore(), dummy.GetScore());
		EXPECT_EQ((*it).GetName(), dummy.GetName());
	}

	// ノード一個のリスト（絶対先頭になる）
	// EXPECT HEAD (DATA1)
	TEST(HeadIteratorTest, 24_SingleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.End(), data1);
		DoublyLinkedList::Iterator it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 二つを先頭で挿入する
	// 前の先頭を移動する
	// EXPECT HEAD (DATA1)
	TEST(HeadIteratorTest, 25_DoubleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		DoublyLinkedList::Iterator it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}
	
	// 客挿入場所チェック
	// EXPECT HEAD (DATA1)
	TEST(HeadIteratorTest, 26_EntryAndCall)
	{
		DoublyLinkedList list1;
		DoublyLinkedList list2;
		DoublyLinkedList list3;
		ScoreData data1(1, "pie");
		list1.Insert(list1.Begin(), data1);
		DoublyLinkedList::Iterator it = list1.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list2.Insert(list2.End(), data1);
		it = list2.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list3.Insert(list3.Last(), data1);
		it = list3.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 先頭から解除
	// EXPECT HEAD (variable)
	TEST(HeadIteratorTest, 27_DeleteAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		ScoreData data4(4, "cookie");
		// Head 4 - 3 - 2 - 1 Tail
		// EXPECT 4	
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		list.Insert(list.Begin(), data3);
		list.Insert(list.Begin(), data4);

		DoublyLinkedList::Iterator it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data4.GetScore());
		EXPECT_EQ((*it).GetName(), data4.GetName());

		// Head 3 - 2 - 1 Tail
		// EXPECT 3
		list.Delete(list.Begin());
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 3 - 2 Tail
		// EXPECT 3
		list.Delete(list.End());
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 3 Tail
		// EXPECT 3
		list.Delete(list.FindByName("cake"));
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());
	}
	
	// --------------------------- //
	// --- 先頭コンストイテレータ --- //
	// --------------------------- //
	// 以下のテストはイテレータよりコンストイテレータを使う

	// 空きリストの先頭イテレータ
	// EXPECT DUMMY
	TEST(HeadConstIteratorTest, 29_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::ConstIterator it = list.cBegin();
		ScoreData dummy(0, "");

		EXPECT_EQ((*it).GetScore(), dummy.GetScore());
		EXPECT_EQ((*it).GetName(), dummy.GetName());
	}

	// ノード一個のリスト（絶対先頭になる）
	// EXPECT HEAD (DATA1)
	TEST(HeadConstIteratorTest, 30_SingleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.End(), data1);
		DoublyLinkedList::ConstIterator it = list.cBegin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 二つを先頭で挿入する
	// 前の先頭を移動する
	// EXPECT HEAD (DATA1)
	TEST(HeadConstIteratorTest, 31_DoubleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.cEnd(), data1);
		list.Insert(list.cEnd(), data2);
		DoublyLinkedList::ConstIterator it = list.cBegin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 客挿入場所チェック
	// EXPECT HEAD (DATA1)
	TEST(HeadConstIteratorTest, 32_EntryAndCall)
	{
		DoublyLinkedList list1;
		DoublyLinkedList list2;
		DoublyLinkedList list3;
		ScoreData data1(1, "pie");
		list1.Insert(list1.cBegin(), data1);
		DoublyLinkedList::ConstIterator it = list1.cBegin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list2.Insert(list2.cEnd(), data1);
		it = list2.cBegin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list3.Insert(list3.cLast(), data1);
		it = list3.cBegin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 先頭から解除
	// EXPECT HEAD (variable)
	TEST(HeadConstIteratorTest, 33_DeleteAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		ScoreData data4(4, "cookie");
		// Head 4 - 3 - 2 - 1 Tail
		// EXPECT 4	
		list.Insert(list.cBegin(), data1);
		list.Insert(list.cBegin(), data2);
		list.Insert(list.cBegin(), data3);
		list.Insert(list.cBegin(), data4);

		DoublyLinkedList::ConstIterator it = list.cBegin();

		EXPECT_EQ((*it).GetScore(), data4.GetScore());
		EXPECT_EQ((*it).GetName(), data4.GetName());

		// Head 3 - 2 - 1 Tail
		// EXPECT 3
		list.Delete(list.Begin());
		it = list.cBegin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 3 - 2 Tail
		// EXPECT 3
		list.Delete(list.End());
		it = list.cBegin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 3 Tail
		// EXPECT 3
		list.Delete(list.FindByName("cake"));
		it = list.cBegin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());
	}

	// -------------------- //
	// --- 末尾イテレータ --- //
	// -------------------- //
	// ノート： Last() != End()
	// Lastは最後のノード
	// End は最後のノード+1

	// 空きリストの末尾イテレータ
	// EXPECT DUMMY
	TEST(EndIteratorTest, 35_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it = list.End();
		ScoreData dummy(0, "");

		EXPECT_EQ((*it).GetScore(), dummy.GetScore());
		EXPECT_EQ((*it).GetName(), dummy.GetName());
	}

	// ノード一個のリスト（絶対末尾になる）
	// EXPECT TAIL (data1)
	TEST(EndIteratorTest, 36_SingleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it = list.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 二つを末尾で挿入する
	// 前の末尾を移動する
	// EXPECT TAIL (data2)
	TEST(EndIteratorTest, 37_DoubleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		DoublyLinkedList::Iterator it = list.Last();

		EXPECT_EQ((*it).GetScore(), data2.GetScore());
		EXPECT_EQ((*it).GetName(), data2.GetName());
	}

	// 客挿入場所チェック
	// EXPECT TAIL (DATA1)
	TEST(EndIteratorTest, 38_EntryAndCall)
	{
		DoublyLinkedList list1;
		DoublyLinkedList list2;
		DoublyLinkedList list3;
		ScoreData data1(1, "pie");
		list1.Insert(list1.End(), data1);
		DoublyLinkedList::Iterator it = list1.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list2.Insert(list2.Begin(), data1);
		it = list2.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list3.Insert(list3.Last(), data1);
		it = list3.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 四つを末尾で購入する
	// 末尾から解除
	// EXPECT TAIL (variable)
	TEST(EndIteratorTest, 39_DeleteAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		ScoreData data4(4, "cookie");
		// Head 1 - 2 - 3 - 4 Tail
		// EXPECT 4
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		list.Insert(list.End(), data3);
		list.Insert(list.End(), data4);

		DoublyLinkedList::Iterator it = list.Last();

		EXPECT_EQ((*it).GetScore(), data4.GetScore());
		EXPECT_EQ((*it).GetName(), data4.GetName());

		// Head 1 - 2 - 3 Tail
		// EXPECT 3
		list.Delete(list.Last());
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 2 - 3 Tail
		// EXPECT 3
		list.Delete(list.Begin());
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 2 Tail
		// EXPECT 2
		list.Delete(list.FindByName("cake"));
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());
	}

	// --------------------------- //
	// --- 末尾コンストイテレータ --- //
	// --------------------------- //
	// 以下のテストはイテレータよりコンストイテレータが使う

	// 空きリストの末尾コンストイテレータ
	TEST(EndConstIteratorTest, 41_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::ConstIterator cit = list.cEnd();
		ScoreData dummy(0, "");

		EXPECT_EQ((*cit).GetScore(), dummy.GetScore());
		EXPECT_EQ((*cit).GetName(), dummy.GetName());
	}

	// ノード一個のリスト（絶対末尾になる）
	// EXPECT TAIL (data1)
	TEST(EndConstIteratorTest, 42_SingleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.cBegin(), data1);
		DoublyLinkedList::ConstIterator cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());
	}

	// 二つを末尾で挿入する
	// 前の末尾を移動する
	// EXPECT TAIL (data1)
	TEST(EndConstIteratorTest, 43_DoubleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.cBegin(), data1);
		list.Insert(list.cBegin(), data2);
		DoublyLinkedList::ConstIterator cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());
	}

	// 客挿入場所
	// EXPECT TAIL (data1)
	TEST(EndConstIteratorTest, 44_EntryAndCall)
	{
		DoublyLinkedList list1;
		DoublyLinkedList list2;
		DoublyLinkedList list3;
		ScoreData data1(1, "pie");

		list1.Insert(list1.cEnd(), data1);
		DoublyLinkedList::ConstIterator cit = list1.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());

		list2.Insert(list2.cBegin(), data1);
		cit = list2.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());

		list3.Insert(list3.FindByName("cake"), data1);
		cit = list3.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());
	}

	// 四つを末尾で購入する
	// 末尾から解除
	// EXPECT TAIL (variable)
	TEST(EndConstIteratorTest, 45_DeleteAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		ScoreData data4(4, "cookie");
		// Head 1 - 2 - 3 - 4 Tail
		// EXPECT 4
		list.Insert(list.cEnd(), data1);
		list.Insert(list.cEnd(), data2);
		list.Insert(list.cEnd(), data3);
		list.Insert(list.cEnd(), data4);

		DoublyLinkedList::ConstIterator cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data4.GetScore());
		EXPECT_EQ((*cit).GetName(), data4.GetName());

		// Head 1 - 2 - 3 Tail
		// EXPECT 3
		list.Delete(list.cLast());
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());

		// Head 2 - 3 Tail
		// EXPECT 3
		list.Delete(list.cBegin());
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());

		// Head 2 Tail
		// EXPECT 2
		list.Delete(list.FindByName("macaron"));
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data2.GetScore());
		EXPECT_EQ((*cit).GetName(), data2.GetName());
	}

}