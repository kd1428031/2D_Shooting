#pragma once

class EnemyBase;

class EnemyManager
{
public:

	~EnemyManager();

	static EnemyManager& GetInstance()
	{
		static EnemyManager instance;
		return instance;
	}

	void Init();
	void Update(float dt);
	void Draw();

	void CreateEnemy(Math::Vector2 pos, float scale = 1.0f);

	std::vector<EnemyBase*> GetEnemy() { return m_enemy; }

private:

	EnemyManager() = default;
	std::vector<EnemyBase*>m_enemy;

};
#define ENEMYMANAGER EnemyManager::GetInstance()