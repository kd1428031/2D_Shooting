#include "main.h"
#include "Scene.h"
#include "Scene/SceneManager.h"
#include "Application/TimeManager.h"
#include "Application/ResourceManager.h"
#include "Application/Audio/AudioManager.h"
#include "Application/Fade/FadeManager.h"
#include "Application/Input/InputManager.h"

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
	ShowCursor(FALSE);
	AUDIOM.Init();
	RESOURCEMANAGER.LoadAll();
	SCENEMANAGER.Init();
	FADEMANAGER.Init();
}

void Scene::Release()
{
	AUDIOM.Release();
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
