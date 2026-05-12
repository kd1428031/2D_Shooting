#pragma once
#include "../BaseScene/BaseScene.h"

class Background;
class EnemyBase;

class GameScene : public BaseScene
{
public:

	enum class Wave
	{
		oen,
		oenBoss,
		two,
		three,
		threeBoss
	};

	GameScene() { Init(); }
	~GameScene() override {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

private:

	Background* m_background;

	bool testKey = false;
	bool testKey2 = false;
	bool testKey3 = false;
	bool testFlg1 = false;

	int m_score;

	bool m_sceneChangeFlg = false;
	bool m_bossMakeFlg = false;
	bool m_bossCreateFlg = false;
	bool m_bossActiveFlg = false;
	bool m_bossDestroyFlg = false;

	bool m_enemyCreate = false;

	float m_timer = 0.0f;

	float m_time = 0.0f;

	Wave m_wave = Wave::oen;

	EnemyBase* m_oneBoss = nullptr;
}; 