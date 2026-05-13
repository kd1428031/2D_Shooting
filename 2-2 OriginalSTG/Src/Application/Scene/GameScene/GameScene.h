#pragma once
#include "../BaseScene/BaseScene.h"

class Background;
class EnemyBase;

class GameScene : public BaseScene
{
public:

	enum class Phase
	{
		Phase1,
		Phase1Boss,
		Phase2,
		Phase3,
		FinalBossIntro,
		FinalBoss,
		GameClear,
		GameOver,
	};

	GameScene() { Init(); }
	~GameScene() override {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

	void UpdatePhase1(float dt);
	void UpdatePhase1Boss(float dt);
	void UpdatePhase2(float dt);
	void UpdatePhase3(float dt);
	void UpdateFinalBossIntro(float dt);
	void UpdateFinalBoss(float dt);
	void UpdateGameClear(float dt);
	void UpdateGameOver(float dt);

	void ChangePhase(Phase phase);

	void IsGameOver();

private:

	Background* m_background;

	bool testKey = false;
	bool testKey2 = false;
	bool testKey3 = false;
	bool testFlg1 = false;

	int m_score;

	float m_phaseTimer = 0.0f;
	float m_spawnTimer = 0.0f;

	Phase m_phase = Phase::Phase1;

	EnemyBase* m_oneBoss = nullptr;

	Math::Matrix m_tutorialShotMat;
	KdTexture *m_tutorialShotTex;
	Math::Color m_color = { 0.8f,0.2f,0.8f,1.0f };
}; 