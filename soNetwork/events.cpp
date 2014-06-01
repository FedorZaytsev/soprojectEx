/*
*	S.T.A.L.K.E.R. Online - Events sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../shared/hook.h"
#include "../shared/log.h"
#include "multipatch.h"

extern CLog* LogHandle;
extern CHook* HookHandle;


void CLevel__cl_Process_CustomEvent(NET_Packet& pack)
{
	if (!HookHandle->IsServer() || (HookHandle->IsServer() && !HookHandle->IsDedicated())) {
		unsigned char type = 0;
		pack.r_u8(type);
		if (type == e_so_engine_packet) {
			unsigned char e;
			pack.r_u8(e);
			switch (e) {
				default:
					LogHandle->Write("CLevel__cl_Process_CustomEvent unknown event %d",e);
					break;
			}
		} else if (type == e_so_script_packet) {
			char data[2048];
			pack.r_stringZ(data);
			LogHandle->Write("Recieved data at client side '%s'",data);
			HookHandle->messanges_cl.push_back(data);
		} else {
			LogHandle->Write("ERROR: CLevel__cl_Process_CustomEvent unknown type");
		}
	}
}
void CLevel__cl_Process_CustomEventServer(NET_Packet& pack)
{
	if (HookHandle->IsServer()) {
		unsigned char type = 0;
		pack.r_u8(type);
		if (type == e_so_engine_packet) {
			unsigned char e;
			pack.r_u8(e);
			switch (e) {
				case e_add_money: {
					LogHandle->Write("CLevel__cl_Process_CustomEventServer add money event");
					ClientID cl_id;
					pack.r_clientID(cl_id);

					HookHandle->Add_money_mp(cl_id);

					}break;
				default:
					LogHandle->Write("CLevel__cl_Process_CustomEventServer unknown event %d",e);
					break;
			}
		} else if (type == e_so_script_packet) {
			char data[2048];
			pack.r_stringZ(data);
			LogHandle->Write("Recieved data at server side '%s'",data);
			HookHandle->messanges_sv.push_back(data);
		} else {
			LogHandle->Write("ERROR: CLevel__cl_Process_CustomEventServer unknown type");
		}
	}
}