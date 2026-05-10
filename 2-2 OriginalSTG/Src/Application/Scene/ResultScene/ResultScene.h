#pragma once
#include "../BaseScene/BaseScene.h"

class Background;

class ResultScene : public BaseScene
{
public:

	ResultScene() { Init(); }
	~ResultScene() override {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

private:

	Background* m_background;

	int m_score;

	bool m_sceneChangeFlg = false;
};