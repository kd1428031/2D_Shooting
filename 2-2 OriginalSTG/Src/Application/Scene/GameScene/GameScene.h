#pragma once
#include "../BaseScene/BaseScene.h"
#include "Application/GameObject/Background/Background.h"

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() override {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

private:

	std::unique_ptr<Background> m_background;

	bool testKey = false;
	bool testFlg1 = false;

	int m_score;
};