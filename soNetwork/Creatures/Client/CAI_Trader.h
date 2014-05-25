/*
*	S.T.A.L.K.E.R. Online - Trader sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CAI_Trader__NET_Export(DWORD pClass,NET_Packet* pack);
void CAI_Trader__NET_Import(DWORD pClass,NET_Packet* pack);