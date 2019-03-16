#pragma once
#include "IHack.h"

#include "CCore.h"
#include "CBaseEntity.h"
#include "Offsets.h"

#include <chrono>
#include <thread>

class CTriggerBot :
	public IHack
{
	DWORD m_dwClientBase;
public:
	CTriggerBot();
	virtual ~CTriggerBot();

	void process() override;
};

