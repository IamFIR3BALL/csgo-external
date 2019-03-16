#pragma once
#include "IHack.h"

#include "CCore.h"
#include "CBaseEntity.h"
#include "Offsets.h"

struct GlowObjectDefinition_t
{
	void* pEntity;
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	uint8_t unk2[14];
};

class CGlowESP :
	public IHack
{
	DWORD m_dwClientBase;
public:
	CGlowESP();
	virtual ~CGlowESP();

	void process() override;
};

