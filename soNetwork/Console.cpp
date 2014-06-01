/*
*	S.T.A.L.K.E.R. Online - Console controll
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <windows.h>

#include "Console.h"
#include "../shared/hook.h"
#include "../shared/log.h"

extern CLog* LogHandle;
extern CHook* HookHandle;
void (_cdecl * game_cl_GameState__u_EventSend1)(NET_Packet &P);
void ConsoleThread(void*)
{
	LogHandle->Write("Console controll thread started");
	while(true)
	{
		
			if(GetAsyncKeyState(VK_F1))
			{
				while(GetAsyncKeyState(VK_LSHIFT)) Sleep(10);
				/*LogHandle->Write("try execute console command SendPacketToAll");
				NET_Packet pack;
				pack.write_start();
				pack.w_begin(0x34);		// 0x33 [51] - MotionsSync
				pack.w_stringZ("Hi stalker");
	
				HookHandle->SendPacketToAll(pack);*/
			}		
			if(GetAsyncKeyState(VK_F2))
			{
				while(GetAsyncKeyState(VK_RSHIFT)) Sleep(10);
				/*LogHandle->Write("try execute console command game_cl_GameState__u_EventSend");

				game_cl_GameState__u_EventSend1 = reinterpret_cast<void (_cdecl *)(NET_Packet &)>((DWORD)(HookHandle->GameOffset) + 0x358CB0);

				DWORD CLevel = (DWORD)g_pGameLevel;
				DWORD game_cl_GameState = (DWORD)((DWORD*)CLevel + 0x486F8);
				NET_Packet P;
				P.write_start();
				P.w_begin(0x32);
				P.w_stringZ("OLOLOLO");
				DWORD pointer = (DWORD)&P;
				_asm {
					push pointer
					mov ecx, game_cl_GameState
					call game_cl_GameState__u_EventSend1
				}*/

				/*LogHandle->Write("try execute console command ");
				NET_Packet pack;
				pack.write_start();
				pack.w_begin(0x34);		// 0x33 [51] - MotionsSync
				pack.w_stringZ("Hi stalker");
	
				HookHandle->SendPacketToAll(pack);*/
			}
			if(GetAsyncKeyState(VK_NUMPAD1))
			{
				while(GetAsyncKeyState(VK_NUMPAD1)) Sleep(10);
				LogHandle->Write("try execute console command mm on");
				HookHandle->Console->Execute("main_menu on");
			}
			if(GetAsyncKeyState(VK_NUMPAD2))
			{
				while(GetAsyncKeyState(VK_NUMPAD2)) Sleep(10);
				LogHandle->Write("try execute console command start server");
				HookHandle->Console->Execute("start server(all/single/alife/new) client(localhost)");
			}
			if(GetAsyncKeyState(VK_NUMPAD3))
			{
				while(GetAsyncKeyState(VK_NUMPAD3)) Sleep(10);
				LogHandle->Write("try execute console command disconnect");
				HookHandle->Console->Execute("disconnect");
			}
		
		Sleep(10);
	}
	LogHandle->Write("Console controll thread completed");
}