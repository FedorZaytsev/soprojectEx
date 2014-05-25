/*
*	S.T.A.L.K.E.R. Online - PsyDog sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CPsyDog__NET_Export(DWORD pClass,NET_Packet* pack);
void CPsyDog__NET_Import(DWORD pClass,NET_Packet* pack);