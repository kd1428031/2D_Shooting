#include "EffectManager.h"
#include "Lightning/Lightning.h"
#include "Lightning/LightningText.h"

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

void EffectManager::CreateEffect(EffectType type, Math::Vector2 pos, float scale)
{
    switch (type)
    {
    case EffectType::Lightning:
        m_Effect.emplace_back(std::make_unique<Lightning>(pos, scale));
        break;

    case EffectType::LightningText:
        m_Effect.emplace_back(std::make_unique<LightningText>(pos, scale));
        break;

    default:
        break;
    }
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
