#include "gtest/gtest.h"
#include "pch.h"
#include "../Project1/DoublyLinkedList.h"

namespace ListTests
{

	// --- 挿入・解除テスト ---

	// 空きリストサイズ
	TEST(AssignmentTest, 0_EmptyList)
	{
		DoublyLinkedList list;
		int count = list.GetSize();
		EXPECT_EQ(count, 0);
	}

	// 末尾で挿入
	TEST(AssignmentTest, 1_TailInsertion)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		list.Insert(list.End(), data);
		EXPECT_EQ(list.GetSize(), 1);
	}

	// 不良データを末尾で挿入
	TEST(AssignmentTest, 2_TailInsertionFailure)
	{
		DoublyLinkedList list;
		ScoreData badData(-150, "");
		list.Insert(list.End(), badData);
		EXPECT_EQ(list.GetSize(), 0);
	}

	// 先頭で挿入成功
	TEST(AssignmentTest, 3_InsertionSuccessful)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		list.Insert(list.Begin(), data);
		EXPECT_EQ(list.GetSize(), 1);
	}

	// 不良データを先頭で挿入
	TEST(AssignmentTest, 4_InsertionFailure)
	{
		DoublyLinkedList list;
		ScoreData badData(-150, "");
		list.Insert(list.Begin(), badData);
		EXPECT_EQ(list.GetSize(), 0);
	}

	// ノードを解除
	TEST(AssignmentTest, 5_Delete)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		list.Insert(list.Begin(), data);
		list.Delete(list.Begin());
		EXPECT_EQ(list.GetSize(), 0);
	}

	// 末尾+1を解除（失敗）
	TEST(AssignmentTest, 6_DeletionFailure)
	{
		DoublyLinkedList list;
		ScoreData data(1, "pie");
		list.Insert(list.Begin(), data);
		list.Delete(list.End());
		EXPECT_EQ(list.GetSize(), 1);
	}

	// 何もところを解除（影響がない)
	TEST(AssignmentTest, 7_EmptyDeletion)
	{
		DoublyLinkedList list;
		list.Delete(list.Begin());
		EXPECT_EQ(list.GetSize(), 0);
	}

	// --- 挿入テスト ---

	// 空きリスト挿入
	TEST(InsertionTest, 9_EmptyInsertion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.End(), data1);
		EXPECT_EQ(list.GetSize(), 1);
	}

	// ノードがあるリストに先頭で挿入
	// 前の先頭が+1に移動する
	TEST(InsertionTest, 10_OccupiedHeadInsertion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		EXPECT_EQ(list.cBegin().GetCurrent()->GetData().GetName(), "cake");
	}

	// ノードがあるリストに末尾で挿入
	//　LastよりEndを使って、新しい末尾（前の末尾に+1）になる
	TEST(InsertionTest, 11_OccupiedTailInsertion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.End(), data1);
		list.Insert(list.End(), data2);
		EXPECT_EQ(list.cBegin().GetCurrent()->GetData().GetName(), "pie");
	}

	// ノードがあるリストの中で挿入
	TEST(InsertionTest, 12_OccupiedMidInsertion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		list.Insert(list.End(), data2);
		list.Insert(list.FindByName("cake"), data3);
		EXPECT_EQ(list.FindByName("macaron").GetNextNode()->GetData().GetName(), "cake");
	}

	// コンストイテレータで挿入
	TEST(InsertionTest, 13_ConstIteratorInsertion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.cBegin(), data1);
		list.Insert(list.cBegin(), data2);
		EXPECT_EQ(list.cBegin().GetNextNode()->GetData().GetName(), "pie");
	}

	// --- データ解除 ---

	// 何もないところを解除
	TEST(DeletionTest, 16_EmptyDeletion)
	{
		DoublyLinkedList list;
		list.Delete(list.Begin());
		list.Delete(list.End());
		EXPECT_FALSE(list.GetSize() != 0);
	}

	// ノード二つ以上リストの先頭を解除
	// 先頭が変える
	TEST(DeletionTest, 17_HeadDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		list.Delete(list.Begin());
		EXPECT_EQ(list.cBegin().GetCurrent()->GetData().GetName(), "pie");
	}

	// ノード二つ以上リストの末尾を解除
	// 末尾が買える
	TEST(DeletionTest, 18_TailDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		list.Delete(list.Last());
		EXPECT_EQ(list.GetSize(), 0);
	}

	// ノードが三つ以上リストの真中を解除
	// 先頭と末尾が変えないがサイズが変わる
	TEST(DeletionTest, 19_MidDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		list.Insert(list.Begin(), data3);
		list.Delete(list.FindByName("pie"));
		EXPECT_EQ(list.cLast().GetCurrent()->GetData().GetName(), "cake");
		EXPECT_EQ(list.GetSize(), 2);
	}

	// コンストイテレータで解除
	TEST(DeletionTest, 20_ConstIteratorDeletion)
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
		EXPECT_EQ(list.cBegin().GetCurrent()->GetData().GetName(), "pie");
	}

	// あってないイテレータ（End）で解除
	TEST(DeletionTest, 21_ImproperIteratorDeletion)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.Begin(), data1);
		list.Delete(list.cEnd());
		EXPECT_TRUE(list.CheckForName("pie"));
	}

	// --- 先頭イテレータ ---

	// 空きリストの先頭イテレータ
	TEST(HeadIteratorTest, 23_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it = list.Begin().GetCurrent();

		EXPECT_EQ((*it).GetScore(), 0);
		EXPECT_EQ((*it).GetName(), "");
	}

	// ノード一個のリスト（絶対先頭になる）
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
	
	// 三つを先頭で挿入する
	// 順番確認
	TEST(HeadIteratorTest, 26_EntryAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.Begin(), data1);
		DoublyLinkedList::Iterator it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list.Insert(list.End(), data2);
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list.Insert(list.FindByName("cake"), data3);
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 四つを先頭で購入する
	// 先頭から解除
	TEST(HeadIteratorTest, 27_DeleteAndCall)
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

		DoublyLinkedList::Iterator it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data4.GetScore());
		EXPECT_EQ((*it).GetName(), data4.GetName());

		// Head 3 - 2 - 1 Tail
		list.Delete(list.Begin());
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 3 - 2 Tail
		list.Delete(list.End());
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 3 Tail
		list.Delete(list.FindByName("cake"));
		it = list.Begin();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());
	}

	// --- 先頭コンストイテレータ ---
	// 以下のテストはイテレータよりコンストイテレータを使う

	// 空きリストの先頭コンストイテレータ
	TEST(HeadConstIteratorTest, 29_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::ConstIterator cit = list.cBegin().GetCurrent();

		EXPECT_EQ((*cit).GetScore(), 0);
		EXPECT_EQ((*cit).GetName(), "");
	}

	// ノード一個のリスト（絶対先頭になる）
	TEST(HeadConstIteratorTest, 30_SingleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		list.Insert(list.cEnd(), data1);
		DoublyLinkedList::ConstIterator cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());
	}
	
	// 二つを先頭で挿入する
	// 前の先頭を移動する
	TEST(HeadConstIteratorTest, 31_DoubleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.cEnd(), data1);
		list.Insert(list.cEnd(), data2);
		DoublyLinkedList::ConstIterator cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());
	}

	// 三つを先頭で挿入する
	// 順番確認
	TEST(HeadConstIteratorTest, 32_EntryAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.cBegin(), data1);
		DoublyLinkedList::ConstIterator cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());

		list.Insert(list.cEnd(), data2);
		cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());

		list.Insert(list.FindByName("cake"), data3);
		cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());
	}

	// 四つを先頭で購入する
	// 先頭から解除
	TEST(HeadConstIteratorTest, 33_DeleteAndCall)
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

		DoublyLinkedList::ConstIterator cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data4.GetScore());
		EXPECT_EQ((*cit).GetName(), data4.GetName());

		// Head 3 - 2 - 1 Tail
		list.Delete(list.cBegin());
		cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());

		// Head 3 - 2 Tail
		list.Delete(list.cEnd());
		cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());

		// Head 3 Tail
		list.Delete(list.FindByName("cake"));
		cit = list.cBegin();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());
	}

	// --- 末尾イテレータ ---

	// 空きリストの末尾イテレータ
	TEST(EndIteratorTest, 35_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::Iterator it = list.End().GetCurrent();

		EXPECT_EQ((*it).GetScore(), 0);
		EXPECT_EQ((*it).GetName(), "");
	}

	// ノード一個のリスト（絶対末尾になる）
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
	TEST(EndIteratorTest, 37_DoubleEntry)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		list.Insert(list.Begin(), data1);
		list.Insert(list.Begin(), data2);
		DoublyLinkedList::Iterator it = list.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 三つを末尾で挿入する
	// 順番確認
	TEST(EndIteratorTest, 38_EntryAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.End(), data1);
		DoublyLinkedList::Iterator it = list.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list.Insert(list.Begin(), data2);
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());

		list.Insert(list.FindByName("cake"), data3);
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data1.GetScore());
		EXPECT_EQ((*it).GetName(), data1.GetName());
	}

	// 四つを末尾で購入する
	// 末尾から解除
	TEST(EndIteratorTest, 39_DeleteAndCall)
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

		DoublyLinkedList::Iterator it = list.Last();

		EXPECT_EQ((*it).GetScore(), data4.GetScore());
		EXPECT_EQ((*it).GetName(), data4.GetName());

		// Head 1 - 2 - 3 Tail
		list.Delete(list.Last());
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 2 - 3 Tail
		list.Delete(list.Begin());
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());

		// Head 2 Tail
		list.Delete(list.FindByName("cake"));
		it = list.Last();

		EXPECT_EQ((*it).GetScore(), data3.GetScore());
		EXPECT_EQ((*it).GetName(), data3.GetName());
	}

	// --- 末尾コンストイテレータ ---
	// 以下のテストはイテレータよりコンストイテレータが使う

	// 空きリストの末尾コンストイテレータ
	TEST(EndConstIteratorTest, 41_EmptyList)
	{
		DoublyLinkedList list;
		DoublyLinkedList::ConstIterator cit = list.cEnd().GetCurrent();

		EXPECT_EQ((*cit).GetScore(), 0);
		EXPECT_EQ((*cit).GetName(), "");
	}

	// ノード一個のリスト（絶対末尾になる）
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

	// 三つを末尾で挿入する
	// 順番確認
	TEST(EndConstIteratorTest, 44_EntryAndCall)
	{
		DoublyLinkedList list;
		ScoreData data1(1, "pie");
		ScoreData data2(2, "cake");
		ScoreData data3(3, "macaron");
		list.Insert(list.cEnd(), data1);
		DoublyLinkedList::ConstIterator cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());

		list.Insert(list.cBegin(), data2);
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());

		list.Insert(list.FindByName("cake"), data3);
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data1.GetScore());
		EXPECT_EQ((*cit).GetName(), data1.GetName());
	}

	// 四つを末尾で購入する
	// 末尾から解除
	TEST(EndConstIteratorTest, 45_DeleteAndCall)
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

		DoublyLinkedList::ConstIterator cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data4.GetScore());
		EXPECT_EQ((*cit).GetName(), data4.GetName());

		// Head 1 - 2 - 3 Tail
		list.Delete(list.cLast());
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());

		// Head 2 - 3 Tail
		list.Delete(list.cBegin());
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());

		// Head 2 Tail
		list.Delete(list.FindByName("cake"));
		cit = list.cLast();

		EXPECT_EQ((*cit).GetScore(), data3.GetScore());
		EXPECT_EQ((*cit).GetName(), data3.GetName());
	}

}