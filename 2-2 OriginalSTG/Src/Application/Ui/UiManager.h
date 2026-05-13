#pragma once
#include "UiBase.h"
#include <SimpleMath.h>

class UiManager
{
public:

	// インスタンス取得用
	static UiManager& GetInstance()
	{
		static UiManager instance;
		return instance;
	}

	~UiManager() = default;

	// 基本処理
	void Init();
	void Update(float dt);
	void Draw();

	void CreateUi(UiType type);

	void Destroy(UiType type);

	bool IsAlive(UiType type)const;

	void SetPos(UiType type, Math::Vector2 pos);
	void SetScale(UiType type, float scale);

	UiBase* GetUi(UiType type);

private:

	UiManager() = default;
	std::vector<std::unique_ptr<UiBase>> m_ui;
};
#define UIMANAGER UiManager::GetInstance()
