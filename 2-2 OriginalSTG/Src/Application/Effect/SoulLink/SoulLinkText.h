#pragma once
#include "Application/Effect/EffectBase.h"

class SoulLinkText : public EffectBase
{
public:

	SoulLinkText(Math::Vector2 pos, float scale);
	~SoulLinkText() = default;

	void Init();
	void Draw() override;

	void UpdateImpl(float dt)override;

	EffectType GetEffectType() const { return EffectType::SoulLinkText; }

private:

	const Math::Color		kInitColor = { 0.9f,0.1f,0.1f,0.0f };
	const Math::Vector2		kInitPos = { 0,0 };
	static constexpr int	kTexWidth = 1024;
	static constexpr int	kTexHeight = 128;
	static constexpr float	kInitScale = 1.0f;

	float m_timer;
};