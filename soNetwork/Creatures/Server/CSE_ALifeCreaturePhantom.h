/*
*	S.T.A.L.K.E.R. Online - Phantom sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../../../shared/hook.h"

// headers
void CSE_ALifeCreaturePhantom__UPDATE_Write(DWORD pClass,NET_Packet* pack);
void CSE_ALifeCreaturePhantom__UPDATE_Read(DWORD pClass,NET_Packet* pack);