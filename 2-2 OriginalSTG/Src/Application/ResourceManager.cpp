#include "ResourceManager.h"

void ResourceManager::LoadAll()
{
    // 自機
    m_tex[TexName::kPlayer].Load("Texture/Player/Player2.png");
    m_tex[TexName::kRaven].Load("Texture/Player/Crow_outline.png");
    m_tex[TexName::kHeart].Load("Texture/Player/HealthUI.png");

    // 敵
    // Daemon
    m_tex[TexName::kDaemon_idle].Load("Texture/Enemy/daemon/IDLE.png");
    m_tex[TexName::kDaemon_hit].Load("Texture/Enemy/daemon/HURT.png");
    m_tex[TexName::kDaemon_death].Load("Texture/Enemy/daemon/DEATH.png");

    // Bat
    m_tex[TexName::kBat].Load("Texture/Enemy/bat/Bat_Sprite_Sheet_light.png");
    
    // GrimReaper
    m_tex[TexName::kGrimReaper_idle].Load("Texture/Enemy/grim_reaper/idle_outline.png");
    m_tex[TexName::kGrimReaper_death].Load("Texture/Enemy/grim_reaper/death_outline.png");
    m_tex[TexName::kGrimReaper_summon].Load("Texture/Enemy/grim_reaper/summon_outline.png");
    m_tex[TexName::kGr_Summon_idle].Load("Texture/Enemy/grim_reaper/summonIdle_outline.png");
    m_tex[TexName::kGr_SummonAppear].Load("Texture/Enemy/grim_reaper/summonAppear_outline.png");
    m_tex[TexName::kGr_Summon_death].Load("Texture/Enemy/grim_reaper/summonDeath_outline.png");
    
    // 弾
    m_tex[TexName::kVioletBullet].Load("Texture/Bullet/VioletBullet.png");
    m_tex[TexName::kPenetratBullet].Load("Texture/Bullet/attackEffect1.png");
    m_tex[TexName::kRedBullet].Load("Texture/Bullet/RedBullet.png");
    m_tex[TexName::kBlackBullet].Load("Texture/Bullet/BlackBullet.png");
    m_tex[TexName::kCrowBullet].Load("Texture/Bullet/crowBullet .png");

    // アイテム
    m_tex[TexName::kHealthPotion].Load("Texture/Item/potion_A_red_full.png");
    
    // 背景
    m_tex[TexName::kBgGame].Load("Texture/Background/Background1.png");

    // Ui
    m_tex[TexName::ktitleName].Load("Texture/Ui/title1.png");
    m_tex[TexName::kPressMessage].Load("Texture/Ui/pressMessage.png");
    m_tex[TexName::kNumber].Load("Texture/Ui/number.png");
    m_tex[TexName::kScore].Load("Texture/Ui/score.png");
    m_tex[TexName::kWarning].Load("Texture/Ui/warning.png");
    m_tex[TexName::kRavenIcon].Load("Texture/Ui/Raven.png");
    m_tex[TexName::kTutorial_shot].Load("Texture/Ui/shot_tutorial.png");
    m_tex[TexName::kX].Load("Texture/Ui/x.png");
    m_tex[TexName::kC].Load("Texture/Ui/c.png");

    // フェード用
    m_tex[TexName::kFade].Load("Texture/fade/fade.png");
    
    // エフェクト
    // ライトニング
    m_tex[TexName::kLightning].Load("Texture/Effect/spritesheet-blue.png");
    m_tex[TexName::kLightningIcon].Load("Texture/Effect/lightningIcon.png");
    m_tex[TexName::kLightningText].Load("Texture/Effect/Lightning.png");
    m_tex[TexName::kSoulLinkText].Load("Texture/Effect/SoulLink.png");
    m_tex[TexName::kHitEffect].Load("Texture/Effect/Circle.png");
    m_tex[TexName::kMpMax].Load("Texture/Effect/spritesheet.png");

    // 魔法陣
    m_tex[TexName::kMagicCircle_idle].Load("Texture/Effect/MagicCircleIdle.png");
    m_tex[TexName::kMagicCircle_summon].Load("Texture/Effect/MagicCircleSummon.png");
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
