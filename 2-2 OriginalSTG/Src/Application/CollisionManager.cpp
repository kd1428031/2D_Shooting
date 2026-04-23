#include "CollisionManager.h"
#include "Application/GameObject/Character/Player/Player.h"
#include "Application/GameObject/Character/Enemy/EnemyBase.h"
#include "Application/GameObject/Bullet/Bullet.h"

void CollisionManager::CheckAll(Player* player,
    std::vector<EnemyBase*>& enemies,
    std::vector<Bullet*>& bullets)
{
    // Ž©‹@ vs “G
    if (!player->IsInvincible())
    {
        for (auto& enemy : enemies)
        {
            if (!enemy->IsAlive()) continue;

            if (IsHit(player->GetPos(), player->GetRadius(),
                enemy->GetPos(), enemy->GetRadius()))
            {
                player->TakeDamage(1);
                enemy->TakeDamage(1);
            }
        }
    }

    // “G vs Ž©‹@’e
    for (auto& enemy : enemies)
    {
        if (!enemy->IsAlive()) continue;

        for (auto& bullet : bullets)
        {
            if (!bullet->IsAlive()) continue;

            if (IsHit(enemy->GetPos(), enemy->GetRadius(),
                bullet->GetPos(), bullet->GetRadius()))
            {
                // ’e‚Í1‘Ì‚Ì“G‚É1‰ñ‚µ‚©“–‚½‚ç‚È‚¢
                if (!bullet->IsAlreadyHit(enemy))
                {
                    enemy->TakeDamage(bullet->GetDamage());

                    if (!bullet->IsPenetrat())
                    {
                        bullet->Destroy();
                    }
                    else
                    {
                        bullet->AddHitEnemy(enemy);
                    }
                }
            }
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