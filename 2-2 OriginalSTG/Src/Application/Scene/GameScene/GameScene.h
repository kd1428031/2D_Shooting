#pragma once
#include "../BaseScene/BaseScene.h"

class Background;
class EnemyBase;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() override {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

	// フェーズ更新
	void UpdatePhase1(float dt);
	void UpdatePhase1Boss(float dt);
	void UpdatePhase2(float dt);
	void UpdatePhase3(float dt);
	void UpdateFinalBossIntro(float dt);
	void UpdateFinalBoss(float dt);
	void UpdateGameClear(float dt);
	void UpdateGameOver(float dt);

	// 自機死亡時	
	void IsGameOver();

	// デバッグ用　必ずリリース時消す=========================
	void DebugKey(float dt);
	void DrawDebug();

private:

	// デバッグ用　必ずリリース時消す=========================
	bool testKey = false;
	bool testKey2 = false;
	bool testKey3 = false;
	bool testFlg1 = false;

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
		Count
	};

	struct PhaseParam
	{
		float timeLimit;
		float spawnInterval;
		float spawnEndTime;
	};

	static constexpr PhaseParam kPhaseParams[(int)Phase::Count] =
	{
		/* Phase1 */		 {30.0f, 10.0f, 20.0f}, //timeLimit,spawnInterval,spawnEndTime
		/* Phase1Boss */	 {0.0f,  0.0f,  0.0f},
		/* Phase2 */		 {40.0f, 5.0f,  30.0f},
		/* Phase3 */		 {40.0f, 10.0f, 30.0f},
		/* FinalBossIntro */ {0.0f,  0.0f,  0.0f},
		/* FinalBoss */		 {0.0f,  0.0f,  0.0f},
		/* GameClear */		 {0.0f,  0.0f,  0.0f},
		/* GameOver */		 {0.0f,  0.0f,  0.0f},
	};

	void ChangePhase(Phase phase);
	const GameScene::PhaseParam& GetPhaseParam(Phase phase) const;

	Phase m_phase = Phase::Phase1;

	float m_phaseTimer = 0.0f;	// フェーズ制御用
	float m_spawnTimer = 0.0f;	// 敵生成制御用

	Background* m_background;

	int m_score;

	static constexpr float	kHitBlinkTime	= 0.2f;	// 点滅継続時間
	static constexpr float	kHitBlinkSpeed	= 1.0f;	// 点滅速度
	const Math::Color		kHitBlinkColor	= { 0.8f, 0.2f, 0.2f, 0.0f };  // 赤色

	EnemyBase* m_oneBoss = nullptr;

	Math::Matrix m_tutorialShotMat;
	KdTexture *m_tutorialShotTex;
	Math::Color m_color = { 0.8f,0.2f,0.8f,1.0f };
}; 