#pragma once

class Player;
class EnemyBase;
class Bullet;

class CollisionManager
{
public:

    static CollisionManager& GetInstance()
    {
        static CollisionManager instance;
        return instance;
    }

    ~CollisionManager() {}

    void CheckAll(Player* player,
        const std::vector<std::unique_ptr<EnemyBase>>& enemies,
        const std::vector<std::unique_ptr<Bullet>>& bullets);

private:

    CollisionManager() {}

    bool IsHit(Math::Vector2 posA, float radiusA,
        Math::Vector2 posB, float radiusB);
};

#define COLLISIONMANAGER CollisionManager::GetInstance()