#include "BulletManager.h"
#include "Application/Scene.h"

void BulletManager::Init()
{
}

void BulletManager::Update(float dt)
{
    for (int i = m_bullet.size() - 1; i >= 0; --i)
    {
        if (m_bullet[i] != nullptr)
        {
            m_bullet[i]->Update(dt);

            if (!m_bullet[i]->IsAlive())
            {
                m_bullet.erase(m_bullet.begin() + i);
            }
        }
    }
}

void BulletManager::Draw()
{
    for (auto& p : m_bullet)
    {
        if (p != nullptr)
        {
            p->Draw();
        }
    }
}

void BulletManager::CreateBullet(BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale, Math::Color color)
{
    auto bullet = std::make_unique<Bullet>(type, pos, velocity, scale, color);
    bullet->Init();
    m_bullet.emplace_back(std::move(bullet));
}

Bullet* BulletManager::GetBullet(int i) const
{
    if (i < 0 || i >= (int)m_bullet.size()) return nullptr;
    return m_bullet[i].get();
}