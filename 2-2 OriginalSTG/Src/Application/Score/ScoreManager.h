#pragma once

class ScoreManager
{
public:

	static ScoreManager& GetInstance()
	{
		static ScoreManager instance;
		return instance;
	}

	~ScoreManager(){}

	void Init() { m_score = 0; };

	int GetScore() const { return m_score; }

	void AddScore(int score) { m_score += score; }

private:

	ScoreManager() { Init(); }

	int m_score;
};
#define SCOREMANAGER ScoreManager::GetInstance()