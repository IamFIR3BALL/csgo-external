#include "CMemory.h"

CMemory::CMemory(std::string szProcessName)
{
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		m_bIsOk = false;
		return;
	}

	if (Process32First(hSnapshot, &procEntry))
	{
		do
		{
			if (_stricmp(szProcessName.c_str(), procEntry.szExeFile) == 0)
			{
				m_Process.hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry.th32ProcessID);
				if (m_Process.hHandle == INVALID_HANDLE_VALUE)
				{
					m_bIsOk = false;
					return;
				}
				m_Process.dwPID = procEntry.th32ProcessID;
				CloseHandle(hSnapshot);
				m_bIsOk = true;
				return;
			}

		} while (Process32Next(hSnapshot, &procEntry));
	}
	CloseHandle(hSnapshot);
	m_bIsOk = false;
}


CMemory::~CMemory()
{
	if(m_Process.hHandle != INVALID_HANDLE_VALUE) CloseHandle(m_Process.hHandle);
}

bool CMemory::addModule(std::string szModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_Process.dwPID);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	MODULEENTRY32 moduleEntry;
	Module mod;
	moduleEntry.dwSize = sizeof(MODULEENTRY32);
	do
	{
		if (!_stricmp(moduleEntry.szModule, szModuleName.c_str()))
		{
			CloseHandle(hSnapshot);
			mod.dwBase = (DWORD)moduleEntry.modBaseAddr;
			mod.hHandle = moduleEntry.hModule;
			mod.dwSize = moduleEntry.dwSize;
			m_vModules.insert(std::pair<std::string, Module>(szModuleName, mod));
			return true;
		}
	} while (Module32Next(hSnapshot, &moduleEntry));
	CloseHandle(hSnapshot);
	return false;
}

bool CMemory::isOk() const
{
	return m_bIsOk;
}

DWORD CMemory::getModuleBase(std::string szModuleName)
{
	return m_vModules[szModuleName].dwBase;
}

DWORD CMemory::getModuleSize(std::string szModuleName)
{
	return m_vModules[szModuleName].dwSize;
}

Module CMemory::getModule(std::string szModuleName)
{
	return m_vModules[szModuleName];
}
