#include "EffectManager.h"
#include "Lightning/Lightning.h"
#include "Lightning/LightningText.h"
#include "SoulLink/SoulLinkText.h"
#include "MagicCircle/MagicCircle.h"

void EffectManager::Init()
{
    m_Effect.clear();
}

void EffectManager::Update(float dt)
{
    for (int i = m_Effect.size() - 1; i >= 0; --i)
    {
        m_Effect[i]->Update(dt);

        // 死んでたら削除
        if (!m_Effect[i]->IsAlive())
        {
            m_Effect.erase(m_Effect.begin() + i);
        }
    }
}

void EffectManager::Draw()
{
    for (auto& p : m_Effect)
    {
        p->Draw();
    }
}

void EffectManager::DrawFront()
{
    for (auto& p : m_Effect)
    {
        p->DrawFront();
    }
}

void EffectManager::DrawBack()
{
    for (auto& p : m_Effect)
    {
        p->DrawBack();
    }
}

EffectBase* EffectManager::CreateEffect(EffectType type, Math::Vector2 pos, float scale)
{
    std::unique_ptr<EffectBase> effectBase;

    switch (type)
    {
    case EffectType::Lightning:
        effectBase = std::make_unique<Lightning>(pos, scale);
        break;

    case EffectType::LightningText:
        effectBase = std::make_unique<LightningText>(pos, scale);
        break;

    case EffectType::SoulLinkText:
        effectBase = std::make_unique<SoulLinkText>(pos, scale);
        break;

    case EffectType::MagicCircle:
        effectBase = std::make_unique<MagicCircle>(pos, scale);
        break;

    default:
        break;
    }

    m_Effect.emplace_back(std::move(effectBase));
    return m_Effect.back().get();
}

void EffectManager::Destroy(EffectType type)
{
    for (auto& Effect : m_Effect)
    {
        if (Effect->GetEffectType() == type)
        {
            Effect->Kill();
        }
    }
}

bool EffectManager::IsAlive(EffectType type) const
{
    for (auto& Effect : m_Effect)
    {
        if (Effect->GetEffectType() == type)
        {
            return Effect->IsAlive();
        }
    }

    return false;
}
