/*
*	S.T.A.L.K.E.R. Online - core hooks for different patches
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "multipatch.h"

// extern
extern BYTE	 PatchVersion;
extern CHook* HookHandle;
extern bool	g_dedicated_server;

// vars
char* fsltx = "./soProject/fsgame.ltx";
char* fsltxd = "../soProject/fsgame.ltx";
char cur_dir[MAX_PATH];

// patch 1.6.0.0

CHook_Patch_00::CHook_Patch_00()
{
	// wait modules load
	while((EngineOffset = GetModuleHandle(L"xrEngine.exe")) == NULL) {}
	while((CoreOffset = GetModuleHandle(L"xrCore.dll")) == NULL) {}
	PatchVersion = 0;
}

void CHook_Patch_00::InstallHooks()
{
	// change offset for file system ltx
	unsigned char bytes[4];
	unsigned long addr;
	if(g_dedicated_server) addr = (unsigned long)fsltxd;
	else addr = (unsigned long)fsltx;
	bytes[0] = (unsigned char)(addr);
	bytes[1] = (unsigned char)(addr >> 8);
	bytes[2] = (unsigned char)(addr >> 16);
	bytes[3] = (unsigned char)(addr >> 24);
	// set offset
	Byte(((unsigned long)CoreOffset + 0xF79C),1,bytes[0]);
	Byte(((unsigned long)CoreOffset + 0xF79D),1,bytes[1]);
	Byte(((unsigned long)CoreOffset + 0xF79E),1,bytes[2]);
	Byte(((unsigned long)CoreOffset + 0xF79F),1,bytes[3]);	

	// dir
	GetCurrentDirectoryA(MAX_PATH,cur_dir);
	// fix path
	if(g_dedicated_server) strcat_s(cur_dir,MAX_PATH,"/../soProject/");
	else strcat_s(cur_dir,MAX_PATH,"/soProject/");

	addr = (unsigned long)cur_dir;
	bytes[0] = (unsigned char)(addr);
	bytes[1] = (unsigned char)(addr >> 8);
	bytes[2] = (unsigned char)(addr >> 16);
	bytes[3] = (unsigned char)(addr >> 24);
	// set offset
	Byte(((unsigned long)CoreOffset + 0xF6E5),1,0x68);
	Byte(((unsigned long)CoreOffset + 0xF6E6),1,bytes[0]);
	Byte(((unsigned long)CoreOffset + 0xF6E7),1,bytes[1]);
	Byte(((unsigned long)CoreOffset + 0xF6E8),1,bytes[2]);
	Byte(((unsigned long)CoreOffset + 0xF6E9),1,bytes[3]);	
}

void CHook_Patch_00::LinkAddresses()
{
	DWORD tmp;
	// link console
	while((tmp = *(DWORD*)GetProcAddress(EngineOffset,"?Console@@3PAVCConsole@@A")) == NULL) Sleep(5);
	Console = (CConsole*)(tmp);
}

IConsole_Command* CHook_Patch_00::CreateConsoleCommand(char* name,void* func)
{
	// create cmd
	IConsole_Command* cmd = new IConsole_Command(name);
	// copy console command ftable
	void* cmd_memory = malloc(0x18);
	memcpy(cmd_memory,cmd->ftable,0x18);
	// set our data
	Address(((unsigned long)cmd_memory),((DWORD)GameOffset + 0x334A10)); // deconstructor set to one of standart cmds (load_last_save)
	Address(((unsigned long)cmd_memory + 4),(unsigned long)(func));
	// relink command ftable
	cmd->ftable = cmd_memory;
	// activate cmd
	cmd->is_custom = 1;
	return cmd;
}

// patch 1.6.0.1

CHook_Patch_01::CHook_Patch_01()
{
	// wait modules load
	while((EngineOffset = GetModuleHandle(L"xrEngine.exe")) == NULL) {}
	while((CoreOffset = GetModuleHandle(L"xrCore.dll")) == NULL) {}
	PatchVersion = 1;
}

void CHook_Patch_01::InstallHooks()
{
}

// patch 1.6.0.2

CHook_Patch_02::CHook_Patch_02()
{
	// wait modules load
	while((EngineOffset = GetModuleHandle(L"xrEngine.exe")) == NULL) {}
	while((CoreOffset = GetModuleHandle(L"xrCore.dll")) == NULL) {}
	PatchVersion = 2;
}

void CHook_Patch_02::InstallHooks()
{
	// change offset for file system ltx
	unsigned char bytes[4];
	unsigned long addr;
	if(g_dedicated_server) addr = (unsigned long)fsltxd;
	else addr = (unsigned long)fsltx;
	bytes[0] = (unsigned char)(addr);
	bytes[1] = (unsigned char)(addr >> 8);
	bytes[2] = (unsigned char)(addr >> 16);
	bytes[3] = (unsigned char)(addr >> 24);
	// set offset
	Byte(((unsigned long)CoreOffset + 0xEDAC),1,bytes[0]);
	Byte(((unsigned long)CoreOffset + 0xEDAD),1,bytes[1]);
	Byte(((unsigned long)CoreOffset + 0xEDAE),1,bytes[2]);
	Byte(((unsigned long)CoreOffset + 0xEDAF),1,bytes[3]);	

	// dir
	GetCurrentDirectoryA(MAX_PATH,cur_dir);
	// fix path
	if(g_dedicated_server) strcat_s(cur_dir,MAX_PATH,"/../soProject/");
	else strcat_s(cur_dir,MAX_PATH,"/soProject/");

	addr = (unsigned long)cur_dir;
	bytes[0] = (unsigned char)(addr);
	bytes[1] = (unsigned char)(addr >> 8);
	bytes[2] = (unsigned char)(addr >> 16);
	bytes[3] = (unsigned char)(addr >> 24);
	// set offset
	Byte(((unsigned long)CoreOffset + 0xECF5),1,0x68);
	Byte(((unsigned long)CoreOffset + 0xECF6),1,bytes[0]);
	Byte(((unsigned long)CoreOffset + 0xECF7),1,bytes[1]);
	Byte(((unsigned long)CoreOffset + 0xECF8),1,bytes[2]);
	Byte(((unsigned long)CoreOffset + 0xECF9),1,bytes[3]);	
}

void CHook_Patch_02::LinkAddresses()
{
	DWORD tmp;
	// link console
	while((tmp = *(DWORD*)GetProcAddress(EngineOffset,"?Console@@3PAVCConsole@@A")) == NULL) Sleep(5);
	Console = (CConsole*)(tmp);

	while((GameOffset = GetModuleHandle(L"xrGame.dll")) == NULL) {}
}

IConsole_Command* CHook_Patch_02::CreateConsoleCommand(char* name,void* func)
{
	// create cmd
	IConsole_Command* cmd = new IConsole_Command(name);
	// copy console command ftable
	void* cmd_memory = malloc(0x18);
	memcpy(cmd_memory,cmd->ftable,0x18);
	// set our data
	Address(((unsigned long)cmd_memory),((DWORD)GameOffset + 0x336FC0)); // deconstructor set to one of standart cmds (load_last_save)
	Address(((unsigned long)cmd_memory + 4),(unsigned long)(func));
	// relink command ftable
	cmd->ftable = cmd_memory;
	// activate cmd
	cmd->is_custom = 1;
	return cmd;
}