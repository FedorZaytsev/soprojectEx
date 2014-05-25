/*
*	S.T.A.L.K.E.R. Online - Controller sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CController__NET_Export(DWORD pClass,NET_Packet* pack);
void CController__NET_Import(DWORD pClass,NET_Packet* pack);