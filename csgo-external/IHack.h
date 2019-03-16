#pragma once

class IHack
{
public:
	IHack() = default;
	virtual ~IHack() = default;

	virtual void process() = 0;
};

