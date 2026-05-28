#pragma once
#include "UiBase.h"

class RavenWaitCounter : public UiBase
{
public:

	RavenWaitCounter();
	~RavenWaitCounter() = default;

	void Init();

	void UpdateImpl(float dt)override;
	void Draw() override;

	void Shake();

	UiType GetUiType() const { return UiType::RavenBomdWaitCounter; }

private:

	const Math::Color		kInitColor = { 1.0f,1.0f,1.0f,1.0f };
	const Math::Vector2		kInitPos = { -170, -300 };
	static constexpr int	kTexFrameWidth = 128;
	static constexpr int	kTexFrameHeight = 128;
	static constexpr float	kInitScale = 0.15f;
	static constexpr int	kTexFrameOffSet = -115;
	static constexpr int	kCountPosOffSet = -8.0f;

	Math::Matrix m_iconMat;
	KdTexture* m_iconTex;
	Math::Color m_iconColor = { 1.0f,1.0f,1.0f,1.0f };

	Math::Matrix m_keyMat;
	KdTexture* m_keyTex;
	Math::Color m_keyColor = { 0.8f,0.2f,0.8f,1.0f };

	float			m_shakeTimer;
	float			m_shakeBlinkTimer;
	int				m_shakePow;
	bool			m_shakeFlg;
	bool			m_shake;
};