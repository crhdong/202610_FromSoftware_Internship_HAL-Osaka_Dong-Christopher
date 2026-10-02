#include "DoublyLinkedList.h"
#include <fstream>

// --- Helpers ---

// Find where the space between the score and name is.
static int StrToInt(const std::string& s, size_t& endPos)
{
	int result = 0;
	endPos = 0;

	while (endPos < s.size() && s[endPos] >= '0' && s[endPos] <= '9')
	{
		result = result * 10 + (s[endPos] - '0');
		endPos++;
	}
	return result;
}

// --- Main ---

void main()
{
	// ファイルを開く
	std::fstream file("Scores.txt");

	DoublyLinkedList scoreList;
	std::string line;

	// ファイルを線でリストにコピーする
	while (std::getline(file, line))
	{
		size_t endPos = 0;
		int score = StrToInt(line, endPos);

		if (endPos >= line.size() || line[endPos] != '\t') continue;

		// スペースの位置 + 1 から
		std::string name = line.substr(endPos + 1);
		
		scoreList.Insert(scoreList.End(), ScoreData(score, name));
	}

	file.close();

	for (ConstIterator it = scoreList.cBegin(); it != scoreList.cEnd(); ++it)
		printf("%d\t%s\n", (*it).GetScore(), (*it).GetName().c_str());

	return;
}