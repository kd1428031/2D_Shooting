#pragma once
#include "UiBase.h"

class GameStart : public UiBase
{
public:

	GameStart();
	~GameStart() = default;

	void Init();

	void UpdateImpl(float dt)override;
	void Draw() override;
	void OnExit()override;

	bool IsClicked() const { return m_isClicked; }

	UiType GetUiType() const { return UiType::GameStart; }

private:

	const Math::Color		kInitColor = { 1.0f,1.0f,1.0f,1.0f };
	const Math::Vector2		kInitPos = { 0.0f, -120.0f };
	static constexpr int	kTexWidth = 1792;
	static constexpr int	kTexHeight = 256;
	static constexpr float	kInitScale = 0.5f;
	static constexpr float	kMaxScale = kInitScale * 1.1f;
	static constexpr float	kScaleChangeSpeed = 10.0f;
	static constexpr float	kExitTime = 1.0f;
	static constexpr float	kBlinkSpeed = 0.5f;
	static constexpr float	kMaxBlinkAlpha = 1.0f;
	static constexpr float	kMinBlinkAlpha = 0.5f;

	float m_exitTimer;

	bool m_isClicked;

	bool m_blink;

	bool m_hoverSoundFlg;
};