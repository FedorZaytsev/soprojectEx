/*
*	S.T.A.L.K.E.R. Online - Phantom sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CPhantom__NET_Export(DWORD pClass,NET_Packet* pack);
void CPhantom__NET_Import(DWORD pClass,NET_Packet* pack);