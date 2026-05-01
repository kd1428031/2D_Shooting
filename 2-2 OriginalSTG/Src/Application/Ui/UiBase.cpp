#include "UiBase.h"

UiBase::UiBase()
    : m_isAlive(true), m_isExiting(false), m_scale(1.0f), m_angle(0.0f), m_tex(nullptr)
{
}

void UiBase::Update(float dt)
{
    if (!m_isAlive)return;

    UpdateImpl(dt);
    UpdateMatrix();
}

void UiBase::UpdateMatrix()
{
	m_mat = CreateMatrix({ 0,0 });
}

void UiBase::Kill()
{
	if (!m_isExiting)
	{
		m_isExiting = true;
		OnExit();
	}
}

void UiBase::OnExit()
{
	m_isAlive = false;
}

Math::Matrix UiBase::CreateMatrix(Math::Vector2 offset)
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
