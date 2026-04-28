#include "WarningCutIn.h"
#include "Application/ResourceManager.h"

WarningCutIn::WarningCutIn()
{
	Init();
}

void WarningCutIn::Init()
{
	RESOURCEMANAGER.GetTex(TexName::kWarning);
	m_pos = {};
	m_velocity = { -5,0 };
}

void WarningCutIn::Draw()
{
}

void WarningCutIn::UpdateImpl(float dt)
{
}
