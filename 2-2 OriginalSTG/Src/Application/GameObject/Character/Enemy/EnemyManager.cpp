#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Daemon/Daemon.h"
#include "Bat/Bat.h"

void EnemyManager::Init()
{
    m_enemy.clear();
}

void EnemyManager::Update(float dt)
{
    for (int i = m_enemy.size() - 1; i >= 0; --i)
    {
        m_enemy[i]->Update(dt);

        // Ž€‚ñ‚Å‚½‚çíœ
        if (!m_enemy[i]->IsAlive())
        {
            m_enemy.erase(m_enemy.begin() + i);
        }
    }
}

void EnemyManager::Draw()
{
    for (auto& p : m_enemy)
    {
        p->Draw();
    }
}

void EnemyManager::CreateEnemy(EnemyType type, Math::Vector2 pos, float scale)
{
    switch (type)
    {
    case EnemyType::Daemon:
    {
        auto enemy = std::make_unique<Daemon>(pos, scale);
        enemy->Init();
        m_enemy.emplace_back(std::move(enemy));

        break;
    }

    case EnemyType::Bat:
    {
        auto enemy = std::make_unique<Bat>(pos, scale);
        enemy->Init();
        m_enemy.emplace_back(std::move(enemy));

        break;
    }

    default:
        break;
    }
}