#pragma once
#include "IHack.h"

#include "CCore.h"
#include "CBaseEntity.h"
#include "Offsets.h"

struct GlowObjectDefinition_t
{
    int32_t m_nNextFreeSlot; //0x0000
    uint32_t pEntity; //0x0004
    float r; //0x0008
    float g; //0x000C
    float b; //0x0010
    float a; //0x0014
    char pad_0018[4]; //0x0018
    float flUnk; //0x001C
    float flBloom; //0x0020
    float localplayeriszeropoint3; //0x0024
    bool m_bRenderWhenOccluded; //0x0028
    bool m_bRenderWhenUnoccluded; //0x0029
    bool m_bFullBloomRender; //0x002A
    char pad_002B[1]; //0x002B
    int32_t m_nFullBloomStencilTestValue; //0x002C
    int32_t iUnk; //0x0030
    int32_t m_nSplitScreenSlot; //0x0034
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

