#pragma once

#include "CCore.h"
#include "Offsets.h"

struct FallbackWeapon
{
	int m_iFallbackPaintkit; // 0x31B8
	int m_iFallbackSeed; // +0x4
	float m_fFallbackWear;
	int m_iFallbackStatTrak;

	FallbackWeapon() {}

	FallbackWeapon(int iFallbackPaintKit, int iFallbackSeed, float fFallbackWear, int iFallbackStatTrak) : m_iFallbackPaintkit(iFallbackPaintKit),
		m_iFallbackSeed(iFallbackSeed), m_fFallbackWear(fFallbackWear), m_iFallbackStatTrak(iFallbackStatTrak)
	{

	}
};

class CBaseEntity
{
	DWORD m_dwBase;
public:
	CBaseEntity(DWORD dwBase);
	~CBaseEntity();

	int getFlags() const;
	

	// CCSPlayer
	int getHP() const;
	int getTeam() const;
	int getCrosshairID() const;
	int getGlowIndex() const;
	int isScoped() const;
	int getActiveWeaponIndex() const;

	// CBaseAttributableItem
	short getItemDefinitionIndex() const;

	void setItemIDHigh(int iIDHigh);

	FallbackWeapon getFallback() const;
	void setFallback(FallbackWeapon tValue) const;

	DWORD getBase() const;
};

