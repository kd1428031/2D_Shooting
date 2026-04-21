#include "BulletManager.h"
#include"Bullet.h"
#include "Application/Scene.h"

BulletManager::~BulletManager()
{
	// I—¹Žž‘Sƒƒ‚ƒŠE—v‘f‰ð•ú
	for (auto& p : m_bullet) delete p;
	m_bullet.clear();
}

void BulletManager::Init()
{
}

void BulletManager::Update(float dt)
{
	// ˆêŠ‡ˆ—
	for (int i = m_bullet.size() - 1; i >= 0; --i)
	{
		if (m_bullet[i] != nullptr)
		{
			m_bullet[i]->Update(dt);

			// Ž€‚ñ‚Å‚½‚çíœ
			if (!m_bullet[i]->IsAlive())
			{
				delete m_bullet[i];
				m_bullet.erase(m_bullet.begin() + i);
			}
		}
	}
}

void BulletManager::Draw()
{
	// ˆêŠ‡•`‰æ
	for (auto& p : m_bullet)
	{
		if (p != nullptr)
		{
			p->Draw();
		}
	}
}

void BulletManager::CreateBullet(Math::Vector2 pos, Math::Vector2 velocity, float scale, Math::Color color)
{
	// ’e¶¬
	Bullet* bullet = new Bullet(pos, velocity, scale, color);
	bullet->Init();
	m_bullet.push_back(bullet);
}

Bullet* BulletManager::GetBullet(int i)
{
	if (i < 0 || i >= (int)m_bullet.size()) return nullptr;
	return m_bullet[i];
}
