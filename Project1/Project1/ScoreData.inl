#include "ScoreData.h"

// -------------------- //
// --- コンストラクタ --- //
// -------------------- //

inline ScoreData::ScoreData()
	: score(-1), name("") { }
inline ScoreData::ScoreData(int i, const std::string& s)
	: score(i), name(s) {
}

// ------------- //
// ---　取得　--- //
// ------------- //

inline int ScoreData::GetScore() const
{
	return score;
}
inline std::string ScoreData::GetName() const
{
	return name;
}

// ------------- //
// --- 上書き --- //
// ------------- //

inline void ScoreData::WriteScore(int newScore)
{
	score = newScore;
}
inline void ScoreData::WriteName(const std::string& newName)
{
	name = newName;
}