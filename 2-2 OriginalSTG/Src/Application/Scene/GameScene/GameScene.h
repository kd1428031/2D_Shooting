#pragma once
#include "../BaseScene/BaseScene.h"

class Background;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() override {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

private:

	Background* m_background;

	bool testKey = false;
	bool testFlg1 = false;

	int m_score;

	bool m_sceneChangeFlg = false;
	bool m_bossMakeFlg = false;
	bool m_bossCreateFlg = false;
	bool m_bossActiveFlg = false;
	bool m_bossDestroyFlg = false;

	bool m_enemyCreate = false;
};