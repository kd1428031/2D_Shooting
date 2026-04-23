#pragma once
#include "UiBase.h"

class ScoreDisplay : public UiBase
{
public:

	ScoreDisplay();
	~ScoreDisplay() = default;

	void Init();

	void DrawImpl()override;


private:

};