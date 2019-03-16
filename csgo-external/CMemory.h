#pragma once

/*

Created 14.09.18 by w0odcr3st

*/

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <map>

struct Module
{
	DWORD dwBase;
	DWORD dwSize;
	HANDLE hHandle;
};

struct Process
{
	HANDLE hHandle;
	DWORD dwPID;
};

class CMemory
{
	Process m_Process;
	std::map<std::string, Module> m_vModules;

	bool m_bIsOk;
public:
	CMemory(std::string szProcessName);
	~CMemory();

	bool addModule(std::string szModuleName);

	bool isOk() const;

	template<typename T>
	void write(DWORD dwAddress, T tValue)
	{
		WriteProcessMemory(m_Process.hHandle, (LPVOID)dwAddress, &tValue, sizeof(T), NULL);
	}

	template<typename T>
	T read(DWORD dwAddress)
	{
		T returned;
		ReadProcessMemory(m_Process.hHandle, (LPVOID)dwAddress, &returned, sizeof(T), NULL);
		return returned;
	}

	template<typename T>
	void read(DWORD dwAddress, T* value)
	{
		ReadProcessMemory(m_Process.hHandle, (LPVOID)dwAddress, value, sizeof(T), NULL);
	}

	DWORD getModuleBase(std::string szModuleName);
	DWORD getModuleSize(std::string szModuleName);
	Module getModule(std::string szModuleName);
};
