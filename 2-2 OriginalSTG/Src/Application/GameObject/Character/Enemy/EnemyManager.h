#pragma once
#include "EnemyBase.h"

enum class EnemyType
{
	Daemon,
	Bat
};

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

	void CreateEnemy(EnemyType type, Math::Vector2 pos, float scale = 1.0f);

	const std::vector < std::unique_ptr<EnemyBase>> &GetEnemy() const { return m_enemy; }

private:

	EnemyManager() = default;
	std::vector < std::unique_ptr<EnemyBase>>m_enemy;

};
#define ENEMYMANAGER EnemyManager::GetInstance()