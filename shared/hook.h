/*
*	S.T.A.L.K.E.R. Online - hook base class
*	Developers:
*		009 (Михайлов Алексей)
*/

#pragma once

#include <windows.h>
#include <malloc.h>

#include "../X-Ray/CApplication.h"
#include "../X-Ray/IGame_Level.h"
#include "../X-Ray/CConsole.h"
#include "../X-Ray/xrMemory.h"
#include "../X-Ray/str_container.h"
#include "../X-Ray/IPureServer.h"
#include "../X-Ray/CLocatorAPI.h"
#include "../X-Ray/IPureClient.h"
#include "../X-Ray/client_id.h"
#include <string>
#include <deque>
#include <map>

using namespace std;

#define PUSH_REG(a) DWORD orig_reg; _asm {mov orig_reg, a}
#define POP_REG(a) _asm {mov a, orig_reg}

__declspec(dllimport) IGame_Level *g_pGameLevel;

class CHook
{
public:
	CHook(void) {}
	~CHook(void) {}
	void Call(unsigned long from,unsigned long to);
	void Jmp(unsigned long from,unsigned long to);
	void JmpEx(unsigned char prefix,unsigned long from,unsigned long to);
	void Byte(unsigned long addr,unsigned int size,unsigned char byte);
	void Address(unsigned long addr,unsigned long data);
	void JoinInClassFtable(unsigned long addr,unsigned long function,unsigned char retn);
	void JoinInClassFtableEx(unsigned long addr,unsigned long function,unsigned char retn,unsigned long& old_function);
	void CreateSwitchTable(unsigned long* locations,unsigned int locations_count,unsigned char* jump_table,unsigned int jump_table_size,unsigned long addr_loc,unsigned long addr_table,unsigned long addr_table_size);
	// multipatch
	virtual void InstallHooks() {}
	virtual void LinkAddresses();
	virtual WORD CreateObject(char* section,char* name,float pos_x,float pos_y,float pos_z,WORD parentid) {return 0xFFFF;}
	virtual void PlayCycle(DWORD pClass,DWORD MotionID) {}
	virtual void PlayCycleEx(DWORD pClass,DWORD unk,DWORD MotionID) {}
	virtual void SendPacketToAll(NET_Packet& pack) {}
	virtual bool IsServer() {return false;}
	virtual bool IsDedicated() {return false;}
	virtual void LoadAImap() {}
	virtual void MessangeRecieved(string s) {}
	virtual void LoadMapScript() {}
	virtual IConsole_Command* CreateConsoleCommand(char* name,void* func) {return NULL;}
	virtual void Connect(char* net_options,DWORD other_data) {}

	CConsole		*Console;
	str_container	*g_pStringContainer;
	xrMemory		*Memory;
	CLocatorAPI		*xr_FS;

	deque<string> messanges_cl;
	deque<string> messanges_sv;

	HMODULE EngineOffset;
	HMODULE CoreOffset;
	HMODULE GameOffset;
	HMODULE NetServerOffset;
	HMODULE PhysicsOffset;
	HMODULE LuaOffset;
	HMODULE RenderOffset;
	int		RenderVersion;
};