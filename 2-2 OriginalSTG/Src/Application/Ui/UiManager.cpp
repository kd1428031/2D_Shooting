#include "UiManager.h"
#include "ScoreDisplay.h"
#include "WarningCutIn.h"

void UiManager::Init()
{
}

void UiManager::Update(float dt)
{
    for (int i = m_ui.size() - 1; i >= 0; --i)
    {
        if (m_ui[i] != nullptr)
        {
            m_ui[i]->Update(dt);

            // 死んでたら削除
            if (!m_ui[i]->IsAlive())
            {
                m_ui.erase(m_ui.begin() + i);  // deleteが不要
            }
        }
    }
}

void UiManager::Draw()
{
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
        m_ui.emplace_back(std::make_unique<ScoreDisplay>());
        break;

    case UiType::WarningCutIn:
        m_ui.emplace_back(std::make_unique<WarningCutIn>());
        break;

    default:
        break;
    }
}