#pragma once
#include "IHack.h"
#include "CCore.h"
#include "CBaseEntity.h"
class CBunnyHop :
	public IHack
{
public:
	CBunnyHop();
	virtual ~CBunnyHop();

	void process() override;
};

