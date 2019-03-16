#include "CBaseEntity.h"



CBaseEntity::CBaseEntity(DWORD dwBase) : m_dwBase(dwBase)
{
}


CBaseEntity::~CBaseEntity()
{
}

int CBaseEntity::getFlags() const
{
	return g_pCore->getMemory()->read<int>(m_dwBase + offset::dwFlags);
}

int CBaseEntity::getHP() const
{
	return g_pCore->getMemory()->read<int>(m_dwBase + offset::dwHealth);
}

int CBaseEntity::getTeam() const
{
	return g_pCore->getMemory()->read<int>(m_dwBase + offset::dwTeamNum);
}

int CBaseEntity::getCrosshairID() const
{
	return g_pCore->getMemory()->read<int>(m_dwBase + offset::dwCrosshairID);
}

int CBaseEntity::getGlowIndex() const
{
	return g_pCore->getMemory()->read<int>(m_dwBase + offset::dwGlowIndex);
}

int CBaseEntity::isScoped() const
{
	return g_pCore->getMemory()->read<int>(m_dwBase + offset::dwScoped);
}

DWORD CBaseEntity::getBase() const
{
	return m_dwBase;
}
