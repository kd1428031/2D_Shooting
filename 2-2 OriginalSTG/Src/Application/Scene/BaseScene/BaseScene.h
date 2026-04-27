#pragma once

// 全てのシーンの親クラス（基底クラス）

class BaseScene
{
public:

	BaseScene() {}
	virtual ~BaseScene() {}

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

private:

};