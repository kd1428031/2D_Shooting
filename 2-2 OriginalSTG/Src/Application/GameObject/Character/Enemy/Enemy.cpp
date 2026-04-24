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
}

void Enemy::UpdateImpl(float dt)
{
	//ShotStraight();
	//ShotNWay(8);
	//ShotAimed();
	ShotRotate(dt);
}

void Enemy::Death(float dt)
{
	m_state = State::Dead;
}
