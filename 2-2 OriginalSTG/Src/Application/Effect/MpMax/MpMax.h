#pragma once
#include "Application/Effect/EffectBase.h"

class MpMax : public EffectBase
{
public:

	MpMax(Math::Vector2 pos, float scale);
	~MpMax() = default;

	void Init();
	void Draw() override {}
	void DrawFront()override;
	void UpdateImpl(float dt)override;

	EffectType GetEffectType() const { return EffectType::MpMax; }

private:

	Math::Vector2 m_velocity;

	const Math::Color		kInitColor = { 1.0f,1.0f,1.0f,1.0f };
	static constexpr int	kTexFrameWidth = 128;
	static constexpr int	kTexFrameHeight = 128;

	static constexpr float kAnimSpeed = 50.0f;
	static constexpr int kAnimMaxX = 31.0f;
};