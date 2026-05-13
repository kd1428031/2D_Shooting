#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Daemon/Daemon.h"
#include "Bat/Bat.h"
#include "GrimReaper/GrimReaper.h"
#include "GrimReaper/Gr_Summon.h"

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

EnemyBase *EnemyManager::CreateEnemy(EnemyType type, Math::Vector2 pos, EnemyBase::ShotType shotType, float scale)
{
    std::unique_ptr<EnemyBase> enemy;

    switch (type)
    {
    case EnemyType::Daemon:
        enemy = std::make_unique<Daemon>(pos, scale);
        break;
    case EnemyType::Bat:
        enemy = std::make_unique<Bat>(pos, scale);
        break;
    case EnemyType::GrimReaper:
        enemy = std::make_unique<GrimReaper>(pos, scale);
        break;
    case EnemyType::Gr_Summon:
        enemy = std::make_unique<Gr_Summon>(pos, scale);
        break;
    }

    if (enemy)
    {
        enemy->Init();
        enemy->SetShotType(shotType);
        m_enemy.emplace_back(std::move(enemy));
        return m_enemy.back().get();
    }
}

void EnemyManager::AllDamage(float damage)
{
    for (auto& p : m_enemy)
    {
        if (p->IsAlive())
        {
            p->TakeDamage(damage);
        }
    }
}

void EnemyManager::AllDestroy()
{
    for (auto& p : m_enemy)
    {
        if (p->IsAlive())
        {
            p->PreDeath();
            p->SetState(EnemyBase::State::Dying);
        }
    }
}

std::vector<EnemyBase*> EnemyManager::GetEnemies(EnemyBase::EnemyTag tag)
{
    std::vector<EnemyBase*> result;

    for (auto& p : m_enemy)
    {
        if (p->GetEnemyTag() == tag && p->IsAlive())
        {
            result.push_back(p.get());
        }
    }

    return result;
}

bool EnemyManager::IsBossAlive()
{
    for (auto& p : m_enemy)
    {
        if (p->GetEnemyTag() == EnemyBase::EnemyTag::Boss)
        {
           return p->IsAlive();
        }
    }
    return false;
}
