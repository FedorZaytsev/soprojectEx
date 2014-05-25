/*
*	S.T.A.L.K.E.R. Online - Core module
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <windows.h>
#include <stdlib.h>

#include <stdio.h>

#include "multipatch.h"
#include "md5.h"
#include "resource.h"

#pragma comment(lib,"../X-Ray libs/xrCore.lib")
#pragma comment(lib,"../X-Ray libs/xrEngine.lib")
#pragma comment(lib,"../X-Ray libs/xrGame.lib")
#pragma comment(lib,"../X-Ray libs/xrCDB.lib")

/*
*	Vars
*/
CHook*	HookHandle;
BYTE	PatchVersion;
bool	g_dedicated_server;
bool	error = false;

/*
*	Headers functions
*/
bool CheckParamExist(wchar_t* paramline,wchar_t* param);
void HookSetup();
void LoadNetworkGame();
void LoadCoopGame();
void GetNetworkVersion();

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
	while(GetModuleHandle(L"xrCore.dll") == NULL) Sleep(100);

	DWORD check_addr = (DWORD)GetModuleHandle(L"xrCore.dll") + 0x12120;
	
	if(*(BYTE*)(check_addr) == 0xC8) HookHandle = new CHook_Patch_00();
	else if(*(BYTE*)(check_addr) == 0x00) HookHandle = new CHook_Patch_01();
	else if(*(BYTE*)(check_addr) == 0x8B) HookHandle = new CHook_Patch_02();
	else MessageBox(NULL,L"Неизвестная версия.",L"S.T.A.L.K.E.R. Online",MB_OK);
	
	HookHandle->InstallHooks();
	HookHandle->LinkAddresses();
}

void MainThread(void*)
{
	// check dedicated
	wchar_t* cmdline = GetCommandLine();
	g_dedicated_server = CheckParamExist(cmdline,L"-dedicated");
	// vars
	IConsole_Command* cmd;
	// hook
	HookSetup();
	// add commands
	// network game
	cmd = HookHandle->CreateConsoleCommand("so_load_network_game",LoadNetworkGame);
	HookHandle->Console->AddCommand(cmd);
	// network version
	cmd = HookHandle->CreateConsoleCommand("so_version_network_game",GetNetworkVersion);
	HookHandle->Console->AddCommand(cmd);
	// load module for dedicated (EDITED: FOR ALL)
	/*if(g_dedicated_server)*/ LoadNetworkGame();
}

void LoadNetworkGame()
{
	if(GetModuleHandle(L"soNetwork.dll") == NULL) 
	{
		if(g_dedicated_server) LoadLibrary(L"../soProject/soNetwork.dll");
		else LoadLibrary(L"./soProject/soNetwork.dll");
	}
}

void GetNetworkVersion()
{
	HMODULE handle = GetModuleHandle(L"soNetwork.dll");
	if(handle != NULL)
	{
		void (__cdecl* GetModuleVersion)(char* dest,int size);
		void (_cdecl * Msg)(char const *, ...);
		char versionstr[64];

		GetModuleVersion = reinterpret_cast<void (_cdecl *)(char* dest,int size)>(GetProcAddress(handle,"?GetModuleVersion@@YAXPADH@Z"));
		Msg = reinterpret_cast<void (_cdecl *)(char const *, ...)>(GetProcAddress(GetModuleHandle(L"xrCore.dll"),"?Msg@@YAXPBDZZ"));
		
		GetModuleVersion(versionstr,64);

		Msg("soNetwork module version: %s",versionstr);
	}
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
			// loadscreen
			HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(IDB_LOADSCREEN), RT_BITMAP);
			HGLOBAL hResLoad = LoadResource(hModule, hRes);
			LPVOID lpResLock = LockResource(hResLoad);

			BYTE currentmd5[16];
			BYTE checkmd5[16] = 
				{0xC1,0x34,0xB7,0x82,0xCB,0x3E,0x30,0x83,0xE4,0x95,0xA0,0xA,0xB9,0x24,0x76,0x71};

			Curl_md5it(currentmd5,(unsigned char*)lpResLock,SizeofResource(hModule, hRes));
			/*
			FILE* out = fopen("md5.txt","w");
			for(int i = 0;i < 16;i++) fprintf(out,"0x%X,",currentmd5[i]);
			fclose(out);
			*/
			// check md5
			int i = 0;
			for(i = 0;i < 16;i++)
			{
				if(currentmd5[i] != checkmd5[i]) break;
			}
			if(i != 16) error = true;
			

			HMODULE hExe = GetModuleHandle(TEXT("xrEngine.exe"));

			HRSRC hRes2 = FindResource(hExe, MAKEINTRESOURCE(123), RT_BITMAP);
			HGLOBAL hRes2Load = LoadResource(hExe, hRes2);
			LPVOID lpRes2Lock = LockResource(hRes2Load);
			
			DWORD oldp;
			VirtualProtect(lpRes2Lock,SizeofResource(hModule, hRes),PAGE_EXECUTE_READWRITE, &oldp);
			memcpy(lpRes2Lock,lpResLock,SizeofResource(hModule, hRes));
			
			// thread
			DWORD threadId = 0; 
			if(!error) 
			{
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&MainThread, 0, 0, (LPDWORD)&threadId);
			}
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			break;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}