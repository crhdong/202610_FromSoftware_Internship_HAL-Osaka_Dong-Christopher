#include "ScoreData.h"


// コンストラクタ
inline ScoreData::ScoreData(int i, const std::string& s)
	: score(i), name(s) {
}

// --- 取得 ---

inline int ScoreData::GetScore() const
{
	return score;
}

inline std::string ScoreData::GetName() const
{
	return name;
}

// --- 上書き ---

// 不良なスコアを書けない
inline void ScoreData::WriteScore(int newScore)
{
	if (score < 0) return;
	score = newScore;
}

// 不良な名前を書けない
inline void ScoreData::WriteName(const std::string& newName)
{
	if (newName == "") return;
	name = newName;
}