/*
*	S.T.A.L.K.E.R. Online - Snork sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CSnork__NET_Export(DWORD pClass,NET_Packet* pack);
void CSnork__NET_Import(DWORD pClass,NET_Packet* pack);