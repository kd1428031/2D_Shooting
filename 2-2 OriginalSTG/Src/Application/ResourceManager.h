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

	~ResourceManager() { ReleaseAll(); }

	// インスタンス取得用
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	void LoadAll();
	void ReleaseAll();

	KdTexture *GetTex(const std::string &name);

private:

	std::map<std::string, KdTexture>m_tex;

	ResourceManager(){}
};
#define RESOURCEMANAGER ResourceManager::GetInstance()