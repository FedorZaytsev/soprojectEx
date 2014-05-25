/*
*	S.T.A.L.K.E.R. Online - CBaseMonster sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CBaseMonster__NET_Export(DWORD pClass,NET_Packet* pack);
void CBaseMonster__NET_Import(DWORD pClass,NET_Packet* pack);