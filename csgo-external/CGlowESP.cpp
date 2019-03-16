#include "CGlowESP.h"



CGlowESP::CGlowESP()
{
	m_dwClientBase = g_pCore->getMemory()->getModule("client_panorama.dll").dwBase;
}


CGlowESP::~CGlowESP()
{
}

void CGlowESP::process()
{
	while (true)
	{
		CBaseEntity cLocalPlayer(g_pCore->getLocalPlayer());
		if (!cLocalPlayer.getBase())
		{
			continue;
		}
		DWORD dwGlowObjectManager = g_pCore->getMemory()->read<DWORD>(m_dwClientBase + offset::dwGlowObjectManager);
		for (int i = 0; i < 32; i++)
		{
			CBaseEntity cEntity(g_pCore->getEntityBaseByIdx(i));
			if (!cEntity.getBase())
			{
				continue;
			}
			if (cEntity.getTeam() != cLocalPlayer.getTeam())
			{
				GlowObjectDefinition_t glow;
				g_pCore->getMemory()->read<GlowObjectDefinition_t>(dwGlowObjectManager + cEntity.getGlowIndex() * sizeof(GlowObjectDefinition_t), &glow);

				int m_iHealth = cEntity.getHP();
				if (m_iHealth >= 50)
				{
					glow.r = 0.0f + (1.0f - (m_iHealth*0.01f));
					glow.g = 1.0f;
					glow.b = 0.f;
					glow.a = 1.f;
				}
				if (m_iHealth < 50)
				{
					glow.r = 1.0f;
					glow.g = 1.0f - (1.0f - (m_iHealth*0.01f));
					glow.b = 0.0f;
					glow.a = 1.0f;
				}
				glow.m_bRenderWhenOccluded = true;
				glow.m_bRenderWhenUnoccluded = false;

				g_pCore->getMemory()->write<GlowObjectDefinition_t>(dwGlowObjectManager + cEntity.getGlowIndex() * sizeof(GlowObjectDefinition_t), glow);
			}
		}
		Sleep(1);
	}
}
