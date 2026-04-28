#pragma once
#include "UiBase.h"

class WarningCutIn  : public UiBase
{
public:

	WarningCutIn ();
	~WarningCutIn () = default;

	void Init();
	void Draw() override;

	void UpdateImpl(float dt)override;

private:

	Math::Vector2 m_velocity;

	const Math::Color		kInitColor	= { 0.8f,0.2f,0.8f,1.0f };
	const Math::Vector2		kInitPos	= { 400, 250 };
	static constexpr int	kTexWidth	= 896;
	static constexpr int	kTexHeight	= 128;
	static constexpr float	kInitScale	= 1.0f;
};