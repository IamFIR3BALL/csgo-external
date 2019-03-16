#pragma once

#include <iostream>
#include <vector>
#include <thread>

#include "Offsets.h"
#include "CMemory.h"
#include "IHack.h"

class CCore
{
	std::shared_ptr<CMemory> m_pMemory;

	std::vector<std::shared_ptr<IHack>> m_pHacks;

	bool m_bIsOk;
public:
	CCore();
	~CCore();
	void process();
	DWORD getEntityBaseByIdx(int idx);
	DWORD getLocalPlayer();
	bool isOk() const;

	void addHack(std::shared_ptr<IHack> pHack);
	void launchHacks();
	std::shared_ptr<CMemory> getMemory();
};

extern CCore* g_pCore;
