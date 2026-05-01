#pragma once
#include "UiBase.h"

class TitleName : public UiBase
{
public:

	TitleName();
	~TitleName() = default;

	void Init();

	void UpdateImpl(float dt)override;
	void Draw() override;
	void OnExit()override;

	UiType GetUiType() const { return UiType::TitleName; }

private:

	const Math::Color		kInitColor = { 0.8f,0.2f,0.8f,1.0f };
	const Math::Vector2		kInitPos = { 0.0f, 200.0f };
	static constexpr int	kTexFrameWidth = 128;
	static constexpr int	kTexFrameHeight = 128;
	static constexpr float	kInitScale = 0.5f;
	static constexpr int	kTexFrameOffSet = -(kTexFrameWidth / 1.5f);
};