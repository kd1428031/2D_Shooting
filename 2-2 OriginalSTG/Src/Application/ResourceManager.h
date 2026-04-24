#pragma once

namespace TexName
{
	constexpr char kPlayer[]	= "player";
	constexpr char kEnemy[]		= "enemy";
	constexpr char kBullet[]	= "bullet";
	constexpr char kBgTitle[]	= "bg_title";
	constexpr char kBgGame[]	= "bg_game";
	constexpr char kBgResult[]	= "bg_result";
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