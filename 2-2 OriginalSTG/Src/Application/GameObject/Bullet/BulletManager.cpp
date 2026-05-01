#include "BulletManager.h"
#include "Application/Scene.h"

void BulletManager::Init()
{
    m_bullet.clear();
}

void BulletManager::Update(float dt)
{
    for (int i = m_bullet.size() - 1; i >= 0; --i)
    {
        m_bullet[i]->Update(dt);

        if (!m_bullet[i]->IsAlive())
        {
            m_bullet.erase(m_bullet.begin() + i);
        }
    }
}

void BulletManager::Draw()
{
    for (auto& p : m_bullet)
    {
        p->Draw();
    }
}

void BulletManager::CreateBullet(BulletOwner owner, BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale, Math::Color color)
{
    auto bullet = std::make_unique<Bullet>(owner, type, pos, velocity, scale, color);
    bullet->Init();
    m_bullet.emplace_back(std::move(bullet));
}