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

	Background* m_background;
};