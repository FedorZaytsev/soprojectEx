/*
*	S.T.A.L.K.E.R. Online - Rat sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CAI_Rat__NET_Export(DWORD pClass,NET_Packet* pack);
void CAI_Rat__NET_Import(DWORD pClass,NET_Packet* pack);