#include "Enemy.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

Enemy::Enemy(Math::Vector2 pos, float scale)
	: EnemyBase(pos, scale)
{
}

void Enemy::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kEnemy);
	m_velocity = { -200,0 };
	m_radius = 32.0f;
	m_angle = 0.0f;
	m_hp = 3;
}

void Enemy::UpdateImpl(float dt)
{

}

void Enemy::Death(float dt)
{
	m_state = State::Dead;
}
