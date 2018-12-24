/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
http://dev-c.com
(C) Alexander Blade 2015
*/
/*
* ALTERED SOURCE
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*/
#include "main.h"

//#include "macros.h"

//#include "Memory\DisableStartupLogos.h"
#include "Util\keyboard.h"
#include "Memory\GTAmemory.h"
#include "Util\FileLogger.h"
#include "Menu\Routine.h"

#include <Windows.h>
#include <Psapi.h>

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		//g_MainModule = hInstance;
		g_MainModule = GetModuleHandle(NULL);

		if (!GetModuleInformation(GetCurrentProcess(), g_MainModule, &g_MainModuleInfo, sizeof(g_MainModuleInfo)))
			ige::myLog << ige::LogType::LOG_ERROR << "Unable to get MODULEINFO from GTA5.exe";

		//DisableRockstarLogos::DisableRockstarLogos();
		//DisableRockstarLogos::DisableLegalMessages();
		GTAmemory::Init();

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRainbowFader, NULL, 0, NULL);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadMenyooConfig, NULL, 0, NULL);

		scriptRegister(hInstance, ThreadMenyooMain);
		scriptRegisterAdditionalThread(hInstance, Thread_menu_loops2);

		keyboardHandlerRegister(OnKeyboardMessage);

		break;

	case DLL_PROCESS_DETACH:
		scriptUnregister(hInstance);
		keyboardHandlerUnregister(OnKeyboardMessage);
		
		break;
	}
	return TRUE;
}

