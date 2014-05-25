/*
*	S.T.A.L.K.E.R. Online - Motions sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../shared/hook.h"

unsigned long CKinematicsAnimated__PlayCycle(unsigned long pClass,unsigned long MotionID,int unknown, DWORD pointer1, DWORD pObject,DWORD unk1);
unsigned long CKinematicsAnimated__PlayCycleEx(unsigned long pClass,unsigned long unk1,unsigned long MotionID,int unknown, DWORD pointer1, DWORD pObject,DWORD unk2);
void CLevel__cl_Process_Motion(NET_Packet& pack);