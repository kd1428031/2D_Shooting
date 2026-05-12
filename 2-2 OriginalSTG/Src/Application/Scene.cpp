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
	//DrawCursor();
}

void Scene::DrawCursor()
{
	Math::Rectangle rect = { 0,0,128,128 };
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex_Color(m_mouseTex, rect, color);
}

void Scene::Update()
{
	TIMEMANAGER.Update();
	float dt = APP.m_deltaTime * TIMEMANAGER.m_timeScale;

	SCENEMANAGER.Update(dt);	

	/*POINT pt = INPUT.GetMousePos();

	m_mouse.x = pt.x;
	m_mouse.y = pt.y;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_mouse.x, m_mouse.y, 1);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(0.4f, 0.4f, 0);
	m_mat = scaleMat * transMat;*/
}

void Scene::Init()
{
	ShowCursor(FALSE);
	AUDIOM.Init();
	RESOURCEMANAGER.LoadAll();
	SCENEMANAGER.Init();
	FADEMANAGER.Init();
	m_mouseTex = RESOURCEMANAGER.GetTex(TexName::kMouseCursor);
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
