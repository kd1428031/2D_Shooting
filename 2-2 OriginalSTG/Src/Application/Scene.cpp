#include "main.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "GameObject/Character/Enemy/EnemyManager.h"
#include "GameObject/Bullet/BulletManager.h"
#include "Ui/UiManager.h"
#include "Input/InputManager.h"

void Scene::Draw2D()
{
	m_background->Draw();
	m_player->Draw();
	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
	UIMANAGER.Draw();
}


void Scene::Update()
{
	TIMEMANAGER.Update();

	float dt = APP.m_deltaTime * TIMEMANAGER.m_timeScale;

	m_player->Update(dt);

	// 採用検討
	//ScrollSpeedChange(dt);
	
	if (GetAsyncKeyState('U') & 0x8000)
	{
		if (!testKey)
		{
			ENEMYMANAGER.CreateEnemy({ 640,0 });
			testKey = true;
		}
	}
	else testKey = false;

	ENEMYMANAGER.Update(dt);
	BULLETMANAGER.Update(dt);
	COLLISIONMANAGER.CheckAll(m_player.get(), ENEMYMANAGER.GetEnemy(), BULLETMANAGER.GetBullet());
	m_background->Update(dt);
	UIMANAGER.Update(dt);
}

void Scene::Init()
{
	RESOURCEMANAGER.LoadAll();

	m_player = std::make_unique<Player>();  
	m_player->Init();
	m_background = std::make_unique<Background>();
	m_background->Init();
	UIMANAGER.CreateUi(UiType::Score);
}

void Scene::Release()
{
}

void Scene::ScrollSpeedChange(float dt)
{
	//スクロール速度を自機入力で加減速(採用検討)
	if (INPUT.IsKeyHeld(VK_RIGHT) || INPUT.IsKeyHeld('D'))
	{
		m_scrollSpeed += m_player->GetSpeed() / 2 * dt;
	}
	if (INPUT.IsKeyHeld(VK_LEFT) || INPUT.IsKeyHeld('A'))
	{
		m_scrollSpeed -= m_player->GetSpeed() / 2 * dt;
	}

	// 速度制限
	if (m_scrollSpeed > kMaxScrollSpeed) m_scrollSpeed = kMaxScrollSpeed;
	if (m_scrollSpeed < kMinScrollSpeed) m_scrollSpeed = kMinScrollSpeed;
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
