/*
*	S.T.A.L.K.E.R. Online - Bloodsucker sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CAI_Bloodsucker__NET_Export(DWORD pClass,NET_Packet* pack);
void CAI_Bloodsucker__NET_Import(DWORD pClass,NET_Packet* pack);