/*
*	S.T.A.L.K.E.R. Online - Chimera sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CChimera__NET_Export(DWORD pClass,NET_Packet* pack);
void CChimera__NET_Import(DWORD pClass,NET_Packet* pack);