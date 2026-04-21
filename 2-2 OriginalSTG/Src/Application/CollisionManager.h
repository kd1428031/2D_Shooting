#pragma once

class Player;
class EnemyBase;
class Bullet;

class CollisionManager
{
public:

	~CollisionManager(){}

	// インスタンス取得用
	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	void CheckAll(Player* player,
		std::vector<EnemyBase*>& enemies,
		std::vector<Bullet*>& bullets);

private:

	CollisionManager(){}

	bool IsHit(Math::Vector2 posA, float radiusA,
		Math::Vector2 posB, float radiusB);
};

#define COLLISIONMANAGER CollisionManager::GetInstance()