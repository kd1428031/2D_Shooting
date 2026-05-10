#include "EffectBase.h"

EffectBase::EffectBase(Math::Vector2 pos, float scale)
	: m_pos(pos),
	m_isAlive(true), m_isExiting(false), m_scale(scale), m_angle(0.0f), m_tex(nullptr)
{
}

void EffectBase::Update(float dt)
{
	if (!m_isAlive)return;

	UpdateImpl(dt);
	UpdateMatrix();
}

void EffectBase::UpdateMatrix()
{
	m_mat = CreateMatrix({ 0,0 });
}

void EffectBase::Kill()
{
	if (!m_isExiting)
	{
		m_isExiting = true;
		OnExit();
	}
}

void EffectBase::OnExit()
{
	m_isAlive = false;
}

Math::Matrix EffectBase::CreateMatrix(Math::Vector2 offset)
{
	Math::Matrix transMat;
	Math::Matrix rotMat;
	Math::Matrix scaleMat;
	Math::Matrix mat;

	scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);
	rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
	transMat = Math::Matrix::CreateTranslation(m_pos.x + offset.x, m_pos.y + offset.y, 0);
	mat = scaleMat * rotMat * transMat;

	return mat;
}

Math::Matrix EffectBase::CreateMatrix(Math::Vector2 pos, Math::Vector2 scale, float angle)
{
	Math::Matrix transMat;
	Math::Matrix rotMat;
	Math::Matrix scaleMat;
	Math::Matrix mat;

	scaleMat = Math::Matrix::CreateScale(scale.x, scale.y, 1);
	rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(angle));
	transMat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
	mat = scaleMat * rotMat * transMat;

	return mat;
}
