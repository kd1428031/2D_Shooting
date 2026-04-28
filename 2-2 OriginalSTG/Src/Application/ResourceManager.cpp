#include "ResourceManager.h"

void ResourceManager::LoadAll()
{
    m_tex[TexName::kPlayer].Load("Texture/Player/Player2.png");
    m_tex[TexName::kEnemy].Load("Texture/Enemy/enemy.png");
    m_tex[TexName::kBullet].Load("Texture/attackEffect1.png");
    m_tex[TexName::kBgGame].Load("Texture/Background/Background1.png");
    m_tex[TexName::kNumber].Load("Texture/Ui/number.png");
    m_tex[TexName::kWarning].Load("Texture/Ui/warning.png");
}

void ResourceManager::ReleaseAll()
{
    m_tex.clear();
}

KdTexture* ResourceManager::GetTex(const std::string &name)
{
    auto it = m_tex.find(name);
    if (it == m_tex.end()) return nullptr;
    return &it->second;
}
