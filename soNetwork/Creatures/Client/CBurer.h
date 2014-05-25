/*
*	S.T.A.L.K.E.R. Online - Burer sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CBurer__NET_Export(DWORD pClass,NET_Packet* pack);
void CBurer__NET_Import(DWORD pClass,NET_Packet* pack);