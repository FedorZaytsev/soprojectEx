/*
*	S.T.A.L.K.E.R. Online - PsyDog sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

#include "../../../shared/hook.h"
#include "CBaseMonster.h"

void CPsyDog__NET_Export(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	CBaseMonster__NET_Export(pClass,pack);

	POP_REG(ecx)
}

void CPsyDog__NET_Import(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)
	
	CBaseMonster__NET_Import(pClass,pack);

	((CObject*)(pClass))->setVisible(1);
	((CObject*)(pClass))->setEnabled(1);
	
	POP_REG(ecx)
}