#include "CTriggerBot.h"



CTriggerBot::CTriggerBot()
{
	m_dwClientBase = g_pCore->getMemory()->getModule("client_panorama.dll").dwBase;
}


CTriggerBot::~CTriggerBot()
{
}

void CTriggerBot::process()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_MENU) < 0)
		{
			CBaseEntity cLocalPlayer(g_pCore->getLocalPlayer());
			if (!cLocalPlayer.getBase())
			{
				continue;
			}
			int m_iCrosshairID = cLocalPlayer.getCrosshairID() - 1;
			if (m_iCrosshairID == -1)
			{
				continue;
			}
			CBaseEntity cEntity(g_pCore->getEntityBaseByIdx(m_iCrosshairID));
			if (cEntity.getTeam() != cLocalPlayer.getTeam() && cLocalPlayer.isScoped())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
