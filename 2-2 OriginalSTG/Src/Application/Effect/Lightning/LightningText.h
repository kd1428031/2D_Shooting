#pragma once
#include "Application/Effect/EffectBase.h"

class LightningText : public EffectBase
{
public:

	LightningText(Math::Vector2 pos, float scale);
	~LightningText() = default;

	void Init();
	void Draw() override;

	void UpdateImpl(float dt)override;

	EffectType GetEffectType() const { return EffectType::Lightning; }

private:

	const Math::Color		kInitColor = { 0.2f,0.2f,0.8f,0.0f };
	const Math::Vector2		kInitPos = { 0,0 };
	static constexpr int	kTexWidth = 896;
	static constexpr int	kTexHeight = 128;
	static constexpr float	kInitScale = 1.0f;

	float m_timer;
};