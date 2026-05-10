#pragma once
#include "EffectBase.h"

class EffectManager
{
public:

	// インスタンス取得用
	static EffectManager& GetInstance()
	{
		static EffectManager instance;
		return instance;
	}

	~EffectManager() = default;

	// 基本処理
	void Init();
	void Update(float dt);
	void Draw();

	void CreateEffect(EffectType type, Math::Vector2 pos, float scale);

	void Destroy(EffectType type);

	bool IsAlive(EffectType type)const;

private:

	EffectManager() = default;
	std::vector<std::unique_ptr<EffectBase>> m_Effect;
};
#define EFFCTMANAGER EffectManager::GetInstance()
