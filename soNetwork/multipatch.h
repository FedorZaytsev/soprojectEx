/*
*	S.T.A.L.K.E.R. Online - network hooks for different patches
*	Developers:
*		009 (Михайлов Алексей)
*/

#pragma once

#include "../shared/hook.h"
enum {
	e_so_script_packet = 0,
	e_so_engine_packet
};
enum {
	e_add_money = 0
};

using namespace std;

class CHook_Patch_00: public CHook
{
public:
	CHook_Patch_00(void);
	~CHook_Patch_00(void);

	void InstallHooks();
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
	WORD CreateObject(char* section,char* name,float pos_x,float pos_y,float pos_z,WORD parentid);
	void PlayCycle(DWORD pClass,DWORD MotionID);
	void PlayCycleEx(DWORD pClass,DWORD unk,DWORD MotionID);
	void SendPacketToAll(NET_Packet& pack);
	bool IsServer();
	bool IsDedicated();
	void LoadAImap();
	void LoadMapScript();
	void Add_money_mp(ClientID cl_id);

};

class CHook_Patch_02_Client: public CHook
{
public:
	CHook_Patch_02_Client(void);
	~CHook_Patch_02_Client(void);

	void InstallHooks();
};