/*
*	S.T.A.L.K.E.R. Online - Events sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../shared/hook.h"

void SendMotionsPacket(unsigned short objectid,NET_Packet& event_pack,unsigned short unknown_const);
void CLevel__cl_Process_CustomEvent(NET_Packet& pack);
void CLevel__cl_Process_CustomEventServer(NET_Packet& pack);