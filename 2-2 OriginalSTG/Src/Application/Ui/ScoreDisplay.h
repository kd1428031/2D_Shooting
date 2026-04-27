#pragma once
#include "UiBase.h"

class ScoreDisplay : public UiBase
{
public:

	ScoreDisplay();
	~ScoreDisplay() = default;

	void Init();

	void UpdateImpl(float dt)override;
	void DrawImpl()override;


private:

	Math::Vector2 m_digitIndex;
	int m_scoreDisplay;

	const Math::Vector2 kInitPos = { -600, 250 };
	static constexpr float kInitScale = 1.0f;
};