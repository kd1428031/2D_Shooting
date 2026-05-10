#include "ResourceManager.h"

void ResourceManager::LoadAll()
{
    // 自機
    m_tex[TexName::kPlayer].Load("Texture/Player/Player2.png");
    m_tex[TexName::kHeart].Load("Texture/Player/HealthUI.png");

    // 敵
    // Daemon
    m_tex[TexName::kDaemon_idle].Load("Texture/Enemy/daemon/IDLE.png");
    m_tex[TexName::kDaemon_hit].Load("Texture/Enemy/daemon/HURT.png");
    m_tex[TexName::kDaemon_death].Load("Texture/Enemy/daemon/DEATH.png");

    // Bat
    m_tex[TexName::kBat].Load("Texture/Enemy/bat/Bat_Sprite_Sheet.png");
    
    // GrimReaper
    m_tex[TexName::kGrimReaper_idle].Load("Texture/Enemy/grim_reaper/idle.png");
    m_tex[TexName::kGrimReaper_death].Load("Texture/Enemy/grim_reaper/death.png");
    m_tex[TexName::kGrimReaper_summon].Load("Texture/Enemy/grim_reaper/summon.png");
    m_tex[TexName::kGr_Summon_idle].Load("Texture/Enemy/grim_reaper/summonIdle.png");
    m_tex[TexName::kGr_SummonAppear].Load("Texture/Enemy/grim_reaper/summonAppear.png");
    m_tex[TexName::kGr_Summon_death].Load("Texture/Enemy/grim_reaper/summonDeath.png");
    
    // 弾
    m_tex[TexName::kBullet].Load("Texture/attackEffect1.png");
    
    // 背景
    m_tex[TexName::kBgGame].Load("Texture/Background/Background1.png");

    // Ui
    m_tex[TexName::ktitleName].Load("Texture/Ui/titlename.png");
    m_tex[TexName::kPressMessage].Load("Texture/Ui/pressMessage.png");
    m_tex[TexName::kNumber].Load("Texture/Ui/number.png");
    m_tex[TexName::kScore].Load("Texture/Ui/score.png");
    m_tex[TexName::kWarning].Load("Texture/Ui/warning.png");
    m_tex[TexName::kStart].Load("Texture/Ui/gamestart.png");
    
    // フェード
    m_tex[TexName::kFade].Load("Texture/fade/fade.png");
    
    // エフェクト
    // ライトニング
    m_tex[TexName::kLightning].Load("Texture/Effect/spritesheet-blue.png");
    m_tex[TexName::kLightningIcon].Load("Texture/Effect/lightningIcon.png");
    m_tex[TexName::kLightningText].Load("Texture/Effect/Lightning.png");
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
