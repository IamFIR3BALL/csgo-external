#include "CCore.h"

CCore* g_pCore = nullptr;

CCore::CCore()
{
	m_pMemory = std::make_shared<CMemory>("csgo.exe");
	if (!m_pMemory->isOk())
	{
		m_bIsOk = false;
		return;
	}
	if (!m_pMemory->addModule("client_panorama.dll"))
	{
		m_bIsOk = false;
		return;
	}
	if (!m_pMemory->addModule("engine.dll"))
	{
		m_bIsOk = false;
		return;
	}
	m_bIsOk = true;
}


CCore::~CCore()
{
}

void CCore::process()
{
	for (auto v : m_pHacks)
	{
		v->process();
	}
}

DWORD CCore::getEntityBaseByIdx(int idx)
{
	static DWORD m_dwClientBase = m_pMemory->getModuleBase("client_panorama.dll");
	return m_pMemory->read<DWORD>(m_dwClientBase + offset::dwEntityList + idx * 0x10);
}

DWORD CCore::getLocalPlayer()
{
	static DWORD m_dwClientBase = m_pMemory->getModuleBase("client_panorama.dll");
	return m_pMemory->read<DWORD>(m_dwClientBase + offset::dwLocalPlayer);
}

bool CCore::isOk() const
{
	return m_bIsOk;
}

void CCore::addHack(std::shared_ptr<IHack> pHack)
{
	m_pHacks.push_back(pHack);
}

void CCore::launchHacks()
{
	for (size_t i = 0; i < m_pHacks.size(); i++)
	{
		std::thread thr(&IHack::process, m_pHacks[i].get());
		thr.detach();
	}
}

std::shared_ptr<CMemory> CCore::getMemory()
{
	return m_pMemory;
}
