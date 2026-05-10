#pragma once
#include "UiBase.h"

class ScoreText : public UiBase
{
public:

	ScoreText();
	~ScoreText() = default;

	void Init();

	void UpdateImpl(float dt)override;
	void Draw() override;
	void OnExit()override;

	UiType GetUiType() const { return UiType::ScoreText; }

private:

	const Math::Color		kInitColor = { 0.8f,0.2f,0.8f,1.0f };
	const Math::Vector2		kInitPos = { 0.0f, -330.0f };
	static constexpr int	kTexWidth = 640;
	static constexpr int	kTexHeight = 128;
	static constexpr float	kInitScale = 0.25f;
	static constexpr float	kExitTime = 1.0f;

	float m_exitTimer;
};