#pragma once
#include "Application/GameObject/GameObject.h"

class Background : public GameObject
{
public:

	Background(){};
	~Background(){};

	void Init()override;
	void Update(float dt)override;
	void Draw()override;

private:

	Math::Matrix m_mat2;

	static constexpr int   kWidth = 1280;
	static constexpr int   kHeight = 720;

	static constexpr float kScrollSpeed = 50;

};