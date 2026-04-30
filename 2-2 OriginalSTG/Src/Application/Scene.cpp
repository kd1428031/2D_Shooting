#include "main.h"
#include "Scene.h"
#include "Scene/SceneManager.h"
#include "Application/TimeManager.h"
#include "Application/ResourceManager.h"

void Scene::Draw2D()
{
	SCENEMANAGER.Draw();	
}

void Scene::Update()
{
	TIMEMANAGER.Update();
	float dt = APP.m_deltaTime * TIMEMANAGER.m_timeScale;

	SCENEMANAGER.Update(dt);	
}

void Scene::Init()
{
	RESOURCEMANAGER.LoadAll();
	SCENEMANAGER.Init();
}

void Scene::Release()
{
}

void Scene::ScrollSpeedChange(float dt)
{
	//スクロール速度を自機入力で加減速(採用検討)
	//if (INPUT.IsKeyHeld(VK_RIGHT) || INPUT.IsKeyHeld('D'))
	//{
	//	m_scrollSpeed += m_player->GetSpeed() / 2 * dt;
	//}
	//if (INPUT.IsKeyHeld(VK_LEFT) || INPUT.IsKeyHeld('A'))
	//{
	//	m_scrollSpeed -= m_player->GetSpeed() / 2 * dt;
	//}

	//// 速度制限
	//if (m_scrollSpeed > kMaxScrollSpeed) m_scrollSpeed = kMaxScrollSpeed;
	//if (m_scrollSpeed < kMinScrollSpeed) m_scrollSpeed = kMinScrollSpeed;
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
