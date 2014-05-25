/*
*	S.T.A.L.K.E.R. Online - smart_terrain fixs
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

#include "../../../shared/hook.h"

bool CWrapperAbstractZone_CSE_ALifeSmartZone___can_switch_online(DWORD pClass)
{
	// в онлайн никогда не переводить
	return false;
}

bool CWrapperAbstractZone_CSE_ALifeSmartZone___can_switch_offline(DWORD pClass)
{
	// если в онлайне то выводим в оффлайн
	if(*(BYTE*)(pClass + 0xA4) == 1) return true;
	else return false;
}