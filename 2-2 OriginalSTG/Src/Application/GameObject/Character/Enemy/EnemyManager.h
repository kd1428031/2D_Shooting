#pragma once
#include "EnemyBase.h"

enum class EnemyType
{
	Daemon,
	Bat,
	GrimReaper,
	Gr_Summon
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

	EnemyBase* CreateEnemy(EnemyType type, Math::Vector2 pos, bool shotFlg = false,
		EnemyBase::ShotType shotType = EnemyBase::ShotType::Straight, float scale = 1.0f);

	void AllDamage(float damage);

	void AllDestroy();

	const std::vector < std::unique_ptr<EnemyBase>> &GetEnemy() const { return m_enemy; }

	std::vector<EnemyBase*> EnemyManager::GetEnemies(EnemyBase::EnemyTag tag);

	bool IsBossAlive();

private:

	EnemyManager() = default;
	std::vector < std::unique_ptr<EnemyBase>>m_enemy;

};
#define ENEMYMANAGER EnemyManager::GetInstance()