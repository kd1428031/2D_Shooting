#include "Enemy.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

Enemy::Enemy(Math::Vector2 pos, float scale)
	: EnemyBase(pos, scale)
{
	m_radius = kRadius;
}

void Enemy::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kEnemy);
	m_velocity = { -30,0 };
	m_hp = 3;
	m_score = 100;
	m_shotTimer = 0.0f;

	m_bulletOffset = kBulletOffsetX;
	m_bulletSpeed = kBulletSpeed;
	m_bulletScale = kBulletScale;
	m_bulletColor = kBulletColor;
	m_bulletAngleSpeed = kBulletAngleSpeed;
}

void Enemy::UpdateImpl(float dt)
{
	m_shotTimer -= dt;
	if (m_shotTimer <= 0)
	{
		ShotStraight();
		//ShotNWay(8);
		//ShotAimed();
		//ShotRotate(dt);
		m_shotTimer = kShotInterval;
	}
}

void Enemy::Death(float dt)
{
	m_state = State::Dead;
}
