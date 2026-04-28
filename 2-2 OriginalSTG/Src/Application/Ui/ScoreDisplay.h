#pragma once
#include "UiBase.h"

class ScoreDisplay : public UiBase
{
public:

	ScoreDisplay();
	~ScoreDisplay() = default;

	void Init();

	void UpdateImpl(float dt)override;
	void Draw() override;
	Math::Matrix CreateMatrix(Math::Vector2 offset);

private:

	const Math::Color		kInitColor		= { 0.8f,0.2f,0.8f,1.0f };
	const Math::Vector2		kInitPos		= { 400, 250 };
	static constexpr int	kTexFrameWidth	= 128;
	static constexpr int	kTexFrameHeight = 128;
	static constexpr float	kInitScale		= 0.5f;
	static constexpr int	kTexFrameOffSet = -(kTexFrameWidth / 1.5f);
};