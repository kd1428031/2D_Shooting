#pragma once

class Bullet;

class BulletManager
{
public:

	~BulletManager();

	// インスタンス取得用
	static BulletManager& GetInstance()
	{
		static BulletManager instance;
		return instance;
	}

	// 基本処理
	void Init();
	void Update(float dt);
	void Draw();

	// 弾を生成する
	void CreateBullet(Math::Vector2 pos, Math::Vector2 velocity, float scale = 1.0f, Math::Color color = { 1,1,1,1 });

	// ゲッター
	Bullet* GetBullet(int i);
	std::vector<Bullet*> GetBullet() { return m_bullet; }

	const int& GetBulletNum() { return m_bullet.size(); }

private:

	BulletManager() = default;
	std::vector<Bullet*>m_bullet;

	// 弾が存在出来る範囲
	const float destroyDistance = 2000;
};

#define BULLETMANAGER BulletManager::GetInstance()