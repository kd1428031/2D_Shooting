#pragma once

namespace TexName
{
	constexpr char kPlayer[] = "player";
	constexpr char kEnemy[] = "enemy";
	constexpr char kBullet[] = "bullet";
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

	void ReleaseAll();

	std::map<std::string, KdTexture>m_tex;

	ResourceManager(){}
};
#define RESOURCEMANAGER ResourceManager::GetInstance()