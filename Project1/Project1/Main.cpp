#include "DoublyLinkedList.h"

void main()
{
	// ファイルを開く
	std::fstream file("Scores.txt");

	DoublyLinkedList scoreList;
	std::string line;

	// ファイルを線でリストにコピーする
	while (std::getline(file, line))
		scoreList.pushBack(line);

	file.close();

	scoreList.printForward();

	return;
}