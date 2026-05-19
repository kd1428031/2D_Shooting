#pragma once
#include "../BaseScene/BaseScene.h"

class Background;

class TitleScene : public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene() override{}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

private:

	static constexpr int kInputDisableTime = 12;
	int m_inputDisableTimer = kInputDisableTime;

	Background* m_background;

	bool m_isExiting;

	bool m_sceneChangeFlg;
};