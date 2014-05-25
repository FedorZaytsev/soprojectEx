/*
*	S.T.A.L.K.E.R. Online - Psy Dog Phantom sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CSE_ALifePsyDogPhantom__UPDATE_Write(DWORD pClass,NET_Packet* pack);
void CSE_ALifePsyDogPhantom__UPDATE_Read(DWORD pClass,NET_Packet* pack);