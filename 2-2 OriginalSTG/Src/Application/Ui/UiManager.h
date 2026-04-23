#pragma once
#include "UiBase.h"

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

private:

	std::vector<std::unique_ptr<UiBase>> m_ui;
};
#define UIMANAGER UiManager::GetInstance()
