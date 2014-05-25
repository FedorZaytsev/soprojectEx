/*
*	S.T.A.L.K.E.R. Online - Fracture sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CFracture__NET_Export(DWORD pClass,NET_Packet* pack);
void CFracture__NET_Import(DWORD pClass,NET_Packet* pack);