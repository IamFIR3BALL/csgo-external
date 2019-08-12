#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <map>
#include <algorithm>

#include "CCore.h"

#include "CGlowESP.h"
#include "CBunnyHop.h"
#include "CTriggerBot.h"

bool parseSettings(std::map<std::string, std::string>& Settings)
{
	std::ifstream settings("settings.cfg", std::ios::in);
	if (!settings.is_open())
	{
		std::cout << "Cannot find settings.cfg, exiting..." << std::endl;
		return 0;
	}
	std::string szTemp;

	// parse settings

	int iCounter = 0;
	while (std::getline(settings, szTemp))
	{
		for (auto it = szTemp.begin(); it != szTemp.end(); ++it)
		{
			if (*it == '=')
			{
				std::string param(szTemp.begin(), it);
				param.erase(std::remove_if(param.begin(), param.end(), isspace));
				it++;
				Settings[param] = std::string(it, szTemp.end());
				std::cout << param << " = " << Settings[param] << std::endl;
			}
		}
	}
	return true;
}

int cstoi(const std::string& str)
{
	return std::stoi(str, nullptr, 16);
}

int main(int argc, char** argv)
{
	std::map<std::string, std::string> settings;
	if (!parseSettings(settings))
	{
		std::cout << "Cannot read config, exiting..." << std::endl;
		return 0;
	}

	/*offset::dwLocalPlayer = cstoi(settings["dwLocalPlayer"]);
	offset::dwHealth = cstoi(settings["dwHealth"]);
	offset::dwGlowIndex = cstoi(settings["dwGlowIndex"]);
	offset::dwTeamNum = cstoi(settings["dwTeamNum"]);
	offset::dwScoped = cstoi(settings["dwScoped"]);
	offset::dwCrosshairID = cstoi(settings["dwCrosshairID"]);
	offset::dwEntityList = cstoi(settings["dwEntityList"]);
	offset::dwGlowObjectManager = cstoi(settings["dwGlowObjectManager"]);*/

	g_pCore = new CCore();
	if (!g_pCore->isOk())
	{
		std::cout << "Cannot construct CCore, exiting..." << std::endl;
		return 0;
	}
	g_pCore->addHack(std::make_shared<CGlowESP>());
	g_pCore->addHack(std::make_shared<CTriggerBot>());
	g_pCore->addHack(std::make_shared<CBunnyHop>());

	g_pCore->launchHacks();

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	delete g_pCore;
}