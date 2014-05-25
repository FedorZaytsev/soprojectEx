/*
*	S.T.A.L.K.E.R. Online - Zombie sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CZombie__NET_Export(DWORD pClass,NET_Packet* pack);
void CZombie__NET_Import(DWORD pClass,NET_Packet* pack);