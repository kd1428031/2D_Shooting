#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Enemy.h"

EnemyManager::~EnemyManager()
{
	// I—¹Žž‘Sƒƒ‚ƒŠE—v‘f‰ð•ú
	for (auto& p : m_enemy) delete p;
	m_enemy.clear();
}

void EnemyManager::Init()
{
}

void EnemyManager::Update(float dt)
{
	// ˆêŠ‡ˆ—
	for (int i = m_enemy.size() - 1; i >= 0; --i)
	{
		if (m_enemy[i] != nullptr)
		{
			m_enemy[i]->Update(dt);

			// Ž€‚ñ‚Å‚½‚çíœ
			if (!m_enemy[i]->IsAlive())
			{
				delete m_enemy[i];
				m_enemy.erase(m_enemy.begin() + i);
			}
		}
	}
}

void EnemyManager::Draw()
{
	// ˆêŠ‡•`‰æ
	for (auto& p : m_enemy)
	{
		if (p != nullptr)
		{
			p->Draw();
		}
	}
}

void EnemyManager::CreateEnemy(Math::Vector2 pos, float scale)
{
	Enemy *enemy = new Enemy(pos, scale);
	enemy->Init();
	m_enemy.push_back(enemy);
}
