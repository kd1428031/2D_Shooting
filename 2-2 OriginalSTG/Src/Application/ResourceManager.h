#pragma once

namespace TexName
{
	constexpr char kPlayer[]			= "player";
	constexpr char kRaven[]				= "raven";
	constexpr char kHeart[]				= "heart";
	constexpr char kDaemon_idle[]		= "daemon";
	constexpr char kDaemon_hit[]		= "daemon_hit";
	constexpr char kDaemon_death[]		= "daemon_death";
	constexpr char kBat[]				= "bat";
	constexpr char kGrimReaper_idle[]	= "grimReaper_idle";
	constexpr char kGrimReaper_death[]	= "grimReaper_death";
	constexpr char kGrimReaper_summon[]	= "grimReaper_summon";
	constexpr char kGr_Summon_idle[]	= "gr_summon_idle";
	constexpr char kGr_SummonAppear[]	= "gr_summon_appear";
	constexpr char kGr_Summon_death[]	= "gr_summon_death";
	constexpr char kBullet[]			= "bullet";
	constexpr char kBgTitle[]			= "bg_title";
	constexpr char kBgGame[]			= "bg_game";
	constexpr char kBgResult[]			= "bg_result";
	constexpr char ktitleName[]			= "titleName";
	constexpr char kPressMessage[]		= "pressMessage";
	constexpr char kNumber[]			= "number";
	constexpr char kScore[]				= "score";
	constexpr char kWarning[]			= "warning";
	constexpr char kStart[]				= "start";
	constexpr char kFade[]				= "fade";
	constexpr char kLightning[]			= "lightning";
	constexpr char kLightningText[]		= "lightningText";
	constexpr char kLightningIcon[]		= "lightningIcon";
	constexpr char kRavenIcon[]			= "ravenIcon";
	constexpr char kSoulLinkText[]		= "soulLinkText";
	constexpr char kMagicCircle_idle[]	= "magicCircleIdle";
	constexpr char kMagicCircle_summon[]= "magicCircleSummon";
	constexpr char kMouseCursor[]		= "mouseCursor";
}

class ResourceManager
{
public:

	// インスタンス取得用
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	~ResourceManager() { ReleaseAll(); }

	void LoadAll();

	KdTexture *GetTex(const std::string &name);

private:

	ResourceManager() = default;

	void ReleaseAll();

	std::map<std::string, KdTexture>m_tex;

};
#define RESOURCEMANAGER ResourceManager::GetInstance()