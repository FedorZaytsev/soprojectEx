/*
*	S.T.A.L.K.E.R. Online - Launcher application
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tlhelp32.h>

#define CORE_LIB_PATH				"./soProject/soCore.dll"
#define DEDICATED_CORE_LIB_PATH		"../soProject/soCore.dll"

void Error()
{
	char str[128];
	sprintf (str, "GetLastError = 0x%x\n", GetLastError());
	MessageBoxA(NULL,str,"info",MB_OK);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	// init vars
	wchar_t cur_dir[MAX_PATH];
	STARTUPINFO sti;
	PROCESS_INFORMATION info;
	HANDLE Process,Thread;
	DWORD ThreadId;
	SIZE_T BytesWritten;
	LPVOID pDllName;
	HANDLE hThread;
	// dir
	GetCurrentDirectory(sizeof(cur_dir),cur_dir);
	// null vars
	ZeroMemory(&sti,sizeof(STARTUPINFO));
	ZeroMemory(&info,sizeof(PROCESS_INFORMATION));
	// set info
	sti.cb = sizeof(STARTUPINFO);
	sti.dwFlags = DETACHED_PROCESS;
	sti.wShowWindow = 1;
	// select app
	if(wcsstr(lpCmdLine,TEXT("-dedicated")))
	{
		// dedicated
		// fix path
		wcscat_s(cur_dir,260,L"/../bin/");
		// start process
		if(CreateProcess(L"../bin/dedicated/xrEngine.exe",lpCmdLine,NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,cur_dir,&sti,&info) == TRUE)
		{
			Process = info.hProcess;
			Thread = info.hThread;
			// attach dll
			pDllName = VirtualAllocEx(Process,NULL,32,MEM_COMMIT,PAGE_READWRITE);
			if(pDllName)
			{
				// core
				if(WriteProcessMemory(Process,pDllName,DEDICATED_CORE_LIB_PATH,strlen(DEDICATED_CORE_LIB_PATH),&BytesWritten))
				{
					hThread = CreateRemoteThread(Process,NULL,NULL,(LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibraryA("kernel32.dll"),"LoadLibraryA"),pDllName,NULL,&ThreadId);
					if(ThreadId)
					{
						WaitForSingleObject(hThread,INFINITE);
						CloseHandle(hThread);
					}
					else Error();
				}
				else Error();
				VirtualFreeEx(Process,pDllName,strlen(DEDICATED_CORE_LIB_PATH),MEM_RELEASE);
			}
			else Error();

			// continue process
			ResumeThread(Thread);
			return 1;
		}
	}
	else if(wcsstr(lpCmdLine,TEXT("-steam"))) 
	{
		HKEY fKey;
		DWORD pcbData = 256;
		TCHAR* steamexe = new TCHAR[pcbData];

		if(RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("Software\\Valve\\Steam"),0,KEY_QUERY_VALUE,&fKey) == ERROR_SUCCESS)
		{
			if(RegQueryValueEx(fKey,TEXT("SteamExe"),NULL,NULL,(LPBYTE)steamexe,&pcbData) == ERROR_SUCCESS) 
			{
				RegCloseKey(fKey);
			}
		}
		
		// replace Stalker-COP.exe
		rename("../Stalker-COP.exe","../Stalker-COP_exe");
		rename("steam-launcher.exe","../Stalker-COP.exe");
		
		if((INT)ShellExecute(0,0,steamexe,TEXT("-applaunch 41700"),0,1) > 32)
		{
			bool found = false;
			HANDLE hProcessSnap;
			while(!found)
			{
				PROCESSENTRY32 pe32;
				pe32.dwSize = sizeof(PROCESSENTRY32);

				hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
				if(Process32First(hProcessSnap,&pe32))
				{
					do
					{
						if(!wcscmp(pe32.szExeFile,L"xrEngine.exe"))
						{
							found = true;
							break;
						}
					}
					while(Process32Next(hProcessSnap,&pe32));
				}
				Sleep(10);
			}
			// game started, replace orig Stalker-COP.exe
			rename("../Stalker-COP.exe","steam-launcher.exe");
			rename("../Stalker-COP_exe","../Stalker-COP.exe");

			return 1;
		}
		else Error();
	}
	else
	{
		// client
		// fix path
		wcscat_s(cur_dir,260,L"/../");
		// start process
		if(CreateProcess(TEXT("../bin/xrEngine.exe"),lpCmdLine,NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,cur_dir,&sti,&info) == TRUE)
		{
			Process = info.hProcess;
			Thread = info.hThread;
			// attach dll
			pDllName = VirtualAllocEx(Process,NULL,strlen(CORE_LIB_PATH),MEM_COMMIT,PAGE_READWRITE);
			if(pDllName)
			{
				if(WriteProcessMemory(Process,pDllName,CORE_LIB_PATH,strlen(CORE_LIB_PATH),&BytesWritten))
				{
					hThread = CreateRemoteThread(Process,NULL,NULL,(LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibraryA("kernel32.dll"),"LoadLibraryA"),pDllName,NULL,&ThreadId);
					if(ThreadId)
					{
						WaitForSingleObject(hThread,INFINITE);
						CloseHandle(hThread);
					}
					else Error();
				}
				else Error();
				VirtualFreeEx(Process,pDllName,strlen(CORE_LIB_PATH),MEM_RELEASE);
			}
			else Error();
			// continue process
			ResumeThread(Thread);
			return 1;
		}
	}
	MessageBox(NULL,L"Error!\nCheck path of mod, need:\nGame directory/soProject/soLauncher.exe",L"S.T.A.L.K.E.R. Online",MB_OK);
	return 1;
}