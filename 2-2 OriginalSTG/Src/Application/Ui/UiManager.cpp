#include "UiManager.h"
#include "ScoreDisplay.h"
#include "WarningCutIn.h"
#include "TitleName.h"
#include "GameStart.h"

void UiManager::Init()
{
    m_ui.clear();
}

void UiManager::Update(float dt)
{
    for (int i = m_ui.size() - 1; i >= 0; --i)
    {
        m_ui[i]->Update(dt);

        // 死んでたら削除
        if (!m_ui[i]->IsAlive())
        {
            m_ui.erase(m_ui.begin() + i);  // deleteが不要
        }
    }
}

void UiManager::Draw()
{
    for (auto& p : m_ui)
    {
        p->Draw();
    }
}

void UiManager::CreateUi(UiType type)
{
    // 重複チェック（現状全UIが1つのみ存在してほしい為チェックしているが要改善）
    for (auto& ui : m_ui)
    {
        if (ui->GetUiType() == type)
        {
            return;
        }
    }

    switch (type)
    {
    case UiType::TitleName:
        m_ui.emplace_back(std::make_unique<TitleName>());
        break;

    case UiType::GameStart:
        m_ui.emplace_back(std::make_unique<GameStart>());
        break;

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

void UiManager::Destroy(UiType type)
{
    for (auto& ui : m_ui)
    {
        if (ui->GetUiType() == type)
        {
            ui->Kill();
        }
    }
}

bool UiManager::IsGameStartButton() const
{
    for (auto& ui : m_ui)
    {
        if (ui->GetUiType() == UiType::GameStart)
        {
            auto* gameStart = static_cast<GameStart*>(ui.get());
            return gameStart->IsClicked();
        }
    }

    return false;
}

bool UiManager::IsAlive(UiType type) const
{
    for (auto& ui : m_ui)
    {
        if (ui->GetUiType() == type)
        {
            return ui->IsAlive();
        }
    }

    return false;
}
