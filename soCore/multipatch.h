/*
*	S.T.A.L.K.E.R. Online - core hooks for different patches
*	Developers:
*		009 (Михайлов Алексей)
*/

#pragma once

#include "../shared/hook.h"

class CHook_Patch_00: public CHook
{
public:
	CHook_Patch_00(void);
	~CHook_Patch_00(void);

	void InstallHooks();
	void LinkAddresses();
	IConsole_Command* CreateConsoleCommand(char* name,void* func);	
};

class CHook_Patch_01: public CHook
{
public:
	CHook_Patch_01(void);
	~CHook_Patch_01(void);

	void InstallHooks();
};

class CHook_Patch_02: public CHook
{
public:
	CHook_Patch_02(void);
	~CHook_Patch_02(void);

	void InstallHooks();
	void LinkAddresses();
	IConsole_Command* CreateConsoleCommand(char* name,void* func);
};