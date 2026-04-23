#include "UiManager.h"
#include "ScoreDisplay.h"

UiManager::~UiManager()
{
	// 終了時全メモリ・要素解放
	for (auto& p : m_ui) delete p;
	m_ui.clear();
}

void UiManager::Init()
{
}

void UiManager::Update(float dt)
{
	// 一括処理
	for (int i = m_ui.size() - 1; i >= 0; --i)
	{
		if (m_ui[i] != nullptr)
		{
			m_ui[i]->Update(dt);

			// 死んでたら削除
			if (!m_ui[i]->IsAlive())
			{
				delete m_ui[i];
				m_ui.erase(m_ui.begin() + i);
			}
		}
	}
}

void UiManager::Draw()
{
	// 一括描画
	for (auto& p : m_ui)
	{
		if (p != nullptr)
		{
			p->Draw();
		}
	}
}

void UiManager::CreateUi(UiType type)
{
	switch (type)
	{
	case UiType::Score:
		m_ui.push_back(new ScoreDisplay());
		break;
	default :
		break;
	}
}
