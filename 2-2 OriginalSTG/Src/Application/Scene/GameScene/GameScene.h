#pragma once
#include "../BaseScene/BaseScene.h"
#include "Application/GameObject/Character/Player/Player.h"
#include "Application/GameObject/Background/Background.h"

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

private:

	std::unique_ptr<Background> m_background;

	bool testKey = false;

	int m_score;
};