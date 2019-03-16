#include "CBunnyHop.h"


#define FL_ONGROUND	(1 << 0)
CBunnyHop::CBunnyHop()
{
}


CBunnyHop::~CBunnyHop()
{
}

void CBunnyHop::process()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_CAPITAL) < 0)
		{
			CBaseEntity cLocalPlayer(g_pCore->getLocalPlayer());
			if (!cLocalPlayer.getBase())
			{
				continue;
			}
			int flags = cLocalPlayer.getFlags();
			if (flags & FL_ONGROUND)
			{
				keybd_event(VK_SPACE, 0x39, 0, 0);
				Sleep(60);
				keybd_event(VK_SPACE, 0x39, KEYEVENTF_KEYUP, 0);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
