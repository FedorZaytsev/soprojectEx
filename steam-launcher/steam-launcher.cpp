// steam-launcher.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tlhelp32.h>

#define CORE_LIB_PATH				"./soProject/soCore.dll"

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
	// start process
	if(CreateProcess(TEXT("./bin/xrEngine.exe"),lpCmdLine,NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,cur_dir,&sti,&info) == TRUE)
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
	}
	else Error();

	return 1;
}