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

	const Math::Vector2 kInitPos = { 400, 250 };
	static constexpr int   kTexFrameSize = 128;
	static constexpr float kInitScale = 0.5f;
	static constexpr int kTexFrameOffSet = -(kTexFrameSize / 1.5f);
};