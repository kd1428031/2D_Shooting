#include "main.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Character/Player/Player.h"
#include "Character/Enemy/EnemyManager.h"
#include "Bullet/BulletManager.h"

void Scene::Draw2D()
{
	player->Draw();
	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
}

void Scene::Update()
{
	TIMEMANAGER.Update();

	float dt = APP.m_deltaTime * TIMEMANAGER.m_timeScale;

	player->Update(dt);

	if(GetAsyncKeyState('U')&0x8000)ENEMYMANAGER.CreateEnemy({0,0});
	ENEMYMANAGER.Update(dt);
	BULLETMANAGER.Update(dt);
	COLLISIONMANAGER.CheckAll(player, ENEMYMANAGER.GetEnemy(),BULLETMANAGER.GetBullet());
}

void Scene::Init()
{
	RESOURCEMANAGER.LoadAll();

	player = new Player();  
	player->Init();
}

void Scene::Release()
{
	delete player;
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
