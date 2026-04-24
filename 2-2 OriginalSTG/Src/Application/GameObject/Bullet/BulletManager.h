#pragma once
#include "Bullet.h"

class BulletManager
{
public:

    static BulletManager& GetInstance()
    {
        static BulletManager instance;
        return instance;
    }

    ~BulletManager() = default;

    void Init();
    void Update(float dt);
    void Draw();

    void CreateBullet(BulletOwner owner, BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale = 1.0f, Math::Color color = { 1,1,1,1 });

    Bullet* GetBullet(int i) const;
    const std::vector<std::unique_ptr<Bullet>>& GetBullet() const { return m_bullet; }
    int GetBulletNum() const { return (int)m_bullet.size(); }

private:

    BulletManager() = default;
    std::vector<std::unique_ptr<Bullet>> m_bullet;
};

#define BULLETMANAGER BulletManager::GetInstance()