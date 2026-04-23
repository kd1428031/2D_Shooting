#pragma once
#include "EnemyBase.h"

class EnemyManager
{
public:

	~EnemyManager() = default;

	static EnemyManager& GetInstance()
	{
		static EnemyManager instance;
		return instance;
	}

	void Init();
	void Update(float dt);
	void Draw();

	void CreateEnemy(Math::Vector2 pos, float scale = 1.0f);

	const std::vector < std::unique_ptr<EnemyBase>> &GetEnemy() const { return m_enemy; }

private:

	EnemyManager() = default;
	std::vector < std::unique_ptr<EnemyBase>>m_enemy;

};
#define ENEMYMANAGER EnemyManager::GetInstance()