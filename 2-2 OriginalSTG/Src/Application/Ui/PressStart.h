#pragma once
#include "UiBase.h"

class PressStart : public UiBase
{
public:

	PressStart();
	~PressStart() = default;

	void Init();

	void UpdateImpl(float dt)override;
	void Draw() override;
	void OnExit()override;

	UiType GetUiType() const { return UiType::PressStart; }

private:

	const Math::Color		kInitColor = { 0.8f,0.2f,0.8f,1.0f };
	const Math::Vector2		kInitPos = { 0.0f, -330.0f };
	static constexpr int	kTexWidth = 1280;
	static constexpr int	kTexHeight = 128;
	static constexpr float	kInitScale = 0.25f;
	static constexpr float	kExitTime = 1.0f;
	static constexpr float	kBlinkSpeed = 1.0f;
	static constexpr float	kMaxBlinkAlpha = 1.0f;
	static constexpr float	kMinBlinkAlpha = 0.2f;

	float m_exitTimer;

	bool m_isClicked;

	bool m_blink;
};