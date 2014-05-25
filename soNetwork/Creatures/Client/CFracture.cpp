/*
*	S.T.A.L.K.E.R. Online - Fracture sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

#include "../../../shared/hook.h"
#include "CBaseMonster.h"

void CFracture__NET_Export(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	CBaseMonster__NET_Export(pClass,pack);

	POP_REG(ecx)
}

void CFracture__NET_Import(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)
	
	CBaseMonster__NET_Import(pClass,pack);

	((CObject*)(pClass))->setVisible(1);
	((CObject*)(pClass))->setEnabled(1);
	
	POP_REG(ecx)
}