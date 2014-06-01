/*
*	S.T.A.L.K.E.R. Online - soNetwork main
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <windows.h>
#include <stdlib.h>

#include "Console.h"
#include "Game.h"
#include "multipatch.h"
#include "../shared/log.h"
#include "resource.h"

#pragma comment(lib,"../X-Ray libs/xrCore.lib")
#pragma comment(lib,"../X-Ray libs/xrEngine.lib")
#pragma comment(lib,"../X-Ray libs/xrGame.lib")
#pragma comment(lib,"../X-Ray libs/xrCDB.lib")
#pragma comment(lib,"../X-Ray libs/xrNetServer.lib")

/*
*	Vars
*/
HANDLE	ConsoleThreadHandle;
HANDLE	GameThreadHandle;
HANDLE	MainThreadHandle;
CLog*	LogHandle;
CHook*	HookHandle;
BYTE	PatchVersion;
bool	g_dedicated_server;

/*
*	Headers functions
*/
bool CheckParamExist(wchar_t* paramline,wchar_t* param);
void HookSetup();
void MainThread(void*);
bool InitClient();
void CloseClient();
__declspec(dllexport) void __cdecl GetModuleVersion(char* dest,int size);

/*
*	Functions body
*/
bool CheckParamExist(wchar_t* paramline,wchar_t* param)
{
	int len1 = wcslen(paramline);
	int len2 = wcslen(param);

	for(int i = 0;i < len1 - len2;i++)
	{
		int j = 0;
		for(;j < len2;j++)
		{
			if(paramline[i + j] != param[j]) break;
		}

		if(j == len2) return true;
	}
	return false;
}

void HookSetup()
{
	while(GetModuleHandle(L"xrGame.dll") == NULL) {}

	DWORD check_addr = (DWORD)GetModuleHandle(L"xrGame.dll") + 0x303039; // 0x30 0x30 0x39 - 009
	
	if(*(BYTE*)(check_addr) == 0xF) HookHandle = new CHook_Patch_00();
	else if(*(BYTE*)(check_addr) == 0x00) HookHandle = new CHook_Patch_01();
	else if(*(BYTE*)(check_addr) == 0xEB) HookHandle = new CHook_Patch_02();
	else MessageBox(NULL,L"Неизвестная версия.",L"S.T.A.L.K.E.R. Online",MB_OK);

	LogHandle->Write("Hook initialized");
	HookHandle->InstallHooks();
	LogHandle->Write("Hooks installed");
}
void HookSetupClient()
{
	while(GetModuleHandle(L"xrGame.dll") == NULL) {}

	DWORD check_addr = (DWORD)GetModuleHandle(L"xrGame.dll") + 0x303039; // 0x30 0x30 0x39 - 009
	
	if(*(BYTE*)(check_addr) == 0xEB) {
		HookHandle = new CHook_Patch_02_Client();
	} else {
		MessageBox(NULL,L"Неподдерживаемая версия.",L"S.T.A.L.K.E.R. Online",MB_OK);
		return;
	}

	LogHandle->Write("Hook initialized");
	HookHandle->InstallHooks();
	LogHandle->Write("Hooks installed");
}

void MainThread(void*)
{
	//if (g_dedicated_server) HookSetupClient();

	// vars
	DWORD threadId = 0; 
	// init hooks
	HookSetup();
	// wait link game objs
	HookHandle->LinkAddresses();
	LogHandle->Write("Console class on address 0x%X",(int)(HookHandle->Console));
	LogHandle->Write("Memory class on address 0x%X",(int)(HookHandle->Memory));
	// create console thread
	ConsoleThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ConsoleThread, 0, 0, (LPDWORD)&threadId);
	// create game thread
//	GameThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&GameThread, 0, 0, (LPDWORD)&threadId);
}

bool InitClient()
{
	// check dedicated
	wchar_t* cmdline = GetCommandLine();
	g_dedicated_server = CheckParamExist(cmdline,L"-dedicated");
	// vars
	DWORD threadId = 0; 
	// init logging
	if(g_dedicated_server) LogHandle = new CLog("../soProject/logs/dedicated_log.txt");
	else LogHandle = new CLog("./soProject/logs/log.txt");
	LogHandle->Write("Logging initialized");
	// create main thread
	MainThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&MainThread, 0, 0, (LPDWORD)&threadId);
	return true;
}

void CloseClient()
{
	TerminateThread(ConsoleThreadHandle,0);
//	TerminateThread(GameThreadHandle,0);
	LogHandle->Write("Client shutdown");
	LogHandle->Write("---------------");
	// delete all
	delete HookHandle;
	delete LogHandle;
}

void __cdecl GetModuleVersion(char* dest,int size)
{
	strcpy_s(dest,size,"1.0.2 release");
}

/*
*	Dll entry point
*/

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hModule);

			if(!InitClient())
			{
				MessageBox(NULL,L"Initialization failed.",L"S.T.A.L.K.E.R. Online",MB_OK);
				return FALSE;
			}
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			CloseClient();
			break;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
