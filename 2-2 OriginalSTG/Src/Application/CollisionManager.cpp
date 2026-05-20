#include "CollisionManager.h"
#include "Application/GameObject/Character/Player/Player.h"
#include "Application/GameObject/Character/Enemy/EnemyBase.h"
#include "Application/GameObject/Bullet/Bullet.h"
#include "Application/GameObject/Item/ItemBase.h"

void CollisionManager::CheckAll(Player* player,
    const std::vector<std::unique_ptr<EnemyBase>>& enemies,
    const std::vector<std::unique_ptr<Bullet>>& bullets,
    const std::vector<std::unique_ptr<ItemBase>>& itemis)
{
    // “G vs Ž©‹@’e
    CheckEnemyVsPlayerBullet(enemies, bullets);

    // ˆÈ‰ºŽ©‹@ŠÖŒW
    if (!player->IsAlive() || player->IsInvincible()) return;

    // Ž©‹@ vs “G
    CheckPlayerVsEnemy(player, enemies);

    // Ž©‹@ vs “G’e
    CheckPlayerVsEnemyBullet(player, bullets);

    // Ž©‹@ vs ƒAƒCƒeƒ€
    CheckPlayerVsItem(player, itemis);
}

void CollisionManager::CheckPlayerVsEnemy(Player* player, const std::vector<std::unique_ptr<EnemyBase>>& enemies)
{
    for (auto& enemy : enemies)
    {
        if (!enemy->IsActive()) continue;

        if (IsHit(player->GetPos(), player->GetRadius(),
            enemy->GetPos(), enemy->GetRadius()))
        {
            player->TakeDamage(1);
            enemy->TakeDamage(1);
        }
    }
}

void CollisionManager::CheckEnemyVsPlayerBullet(const std::vector<std::unique_ptr<EnemyBase>>& enemies, const std::vector<std::unique_ptr<Bullet>>& bullets)
{
    for (auto& enemy : enemies)
    {
        if (!enemy->IsActive()) continue;
        if (enemy->IsInvincible()) continue;

        for (auto& bullet : bullets)
        {
            if (!bullet->IsAlive()) continue;
            if (bullet->GetBulletOwner() == BulletOwner::Enemy) continue;

            if (IsHit(enemy->GetPos(), enemy->GetRadius(),
                bullet->GetPos(), bullet->GetHitRadius()))
            {
                if (!bullet->IsAlreadyHit(enemy.get()))
                {
                    enemy->TakeDamage(bullet->GetDamage());

                    if (!bullet->IsPenetrat())
                    {
                        bullet->Destroy();
                    }
                    else
                    {
                        bullet->AddHitEnemy(enemy.get());
                    }
                }
            }
        }
    }
}

void CollisionManager::CheckPlayerVsEnemyBullet(Player* player, const std::vector<std::unique_ptr<Bullet>>& bullets)
{
    for (auto& bullet : bullets)
    {
        if (!bullet->IsAlive()) continue;
        if (bullet->GetBulletOwner() == BulletOwner::Player) continue;

        if (IsHit(player->GetPos(), player->GetRadius(),
            bullet->GetPos(), bullet->GetHitRadius()))
        {
            player->TakeDamage(1);
            bullet->Destroy();
        }
    }
}

void CollisionManager::CheckPlayerVsItem(Player* player, const std::vector<std::unique_ptr<ItemBase>>& itemis)
{
    for (auto& item : itemis)
    {
        if (!item->IsAlive()) continue;

        if (IsHit(player->GetPos(), player->GetRadius(),
            item->GetPos(), item->GetRadius()))
        {
            item->OnHit(player);
        }
    }
}

bool CollisionManager::IsHit(Math::Vector2 posA, float radiusA, Math::Vector2 posB, float radiusB)
{
    // ‰~Œ`“–‚½‚è”»’è
    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;
    float dist = dx * dx + dy * dy;
    float radius = (radiusA + radiusB) * (radiusA + radiusB);
    return dist <= radius;
}