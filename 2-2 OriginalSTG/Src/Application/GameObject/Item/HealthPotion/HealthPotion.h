#pragma once
#include "Application/GameObject/Item/ItemBase.h"

class Player;

class HealthPotion :public ItemBase
{
public:

	HealthPotion(Math::Vector2 pos, float scale = 1.0f);
	~HealthPotion(){}

	void Init()				override;

	void UpdateImpl(float dt)override;
	void OnHit(Player* player)override;

private:

	static constexpr float  kRadius = 32.0f;
	static constexpr int    kTexFrameWidth = 64.0f;
	static constexpr int    kTexFrameHeight = 64.0f;
	static constexpr int    kHealValue = 1.0f;

};