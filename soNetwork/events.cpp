/*
*	S.T.A.L.K.E.R. Online - Events sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../shared/hook.h"
#include "../shared/log.h"

extern CLog* LogHandle;
extern CHook* HookHandle;

void CLevel__cl_Process_CustomEvent(NET_Packet& pack)
{
	if (!HookHandle->IsServer() || (HookHandle->IsServer() && !HookHandle->IsDedicated())) {
		char data[2048];
		pack.r_stringZ(data);
		LogHandle->Write("Recieved data at client side '%s'",data);
		HookHandle->messanges_cl.push_back(data);
	}
}
void CLevel__cl_Process_CustomEventServer(NET_Packet& pack)
{
	if (HookHandle->IsServer()) {
		char data[2048];
		pack.r_stringZ(data);
		LogHandle->Write("Recieved data at server side '%s'",data);
		HookHandle->messanges_sv.push_back(data);
	}
}