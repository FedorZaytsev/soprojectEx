/*
*	S.T.A.L.K.E.R. Online - Motions sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "../shared/hook.h"
#include "../shared/log.h"
#include "../shared/hook.h"

extern CLog* LogHandle;
extern CHook* HookHandle;
extern DWORD pBlendCorrect;
extern DWORD pCKinematicsAnimated__PlayCycle;
extern DWORD pCControlAnimationBase__select_animation;
extern DWORD pCKinematicsAnimated__PlayCycleEx;
extern void* CustomSyncData_Entity[0xFFFF];

void SendCyclePacket(unsigned short objectid,unsigned long MotionID)
{
	NET_Packet pack;
	pack.write_start();
	pack.w_begin(0x33);		// 0x33 [51] - MotionsSync
	pack.w_u16(objectid);
	pack.w_u8(1);			// type - CKinematicsAnimated::PlayCycle
	pack.w(&MotionID,sizeof(unsigned long));
	
	HookHandle->SendPacketToAll(pack);
}

void SendCycleExPacket(unsigned short objectid,unsigned long unk,unsigned long MotionID)
{
	NET_Packet pack;
	pack.write_start();
	pack.w_begin(0x33);		// 0x33 [51] - MotionsSync
	pack.w_u16(objectid);
	pack.w_u8(2);			// type - CKinematicsAnimated::PlayCycleEx
	pack.w(&unk,sizeof(unsigned long));
	pack.w(&MotionID,sizeof(unsigned long));
	
	HookHandle->SendPacketToAll(pack);
}

unsigned long CKinematicsAnimated__PlayCycle(unsigned long pClass,unsigned long MotionID,int unknown, DWORD pointer1, DWORD pObject,DWORD unk1)
{
	PUSH_REG(ecx)

	unsigned long result = 0;
	
	if(pObject != 0)
	{
		if(MotionID != 0xA0007)
		{
			// get object id
			unsigned short objectid = ((CObject*)pObject)->ID();
			
			// Custom sync
			if(CustomSyncData_Entity[objectid])
			{
				SendCyclePacket(objectid,MotionID);
			}
		}
	}

	_asm
	{
		push unk1
		push pObject
		push pointer1
		push unknown
		push MotionID
		mov ecx, pClass
		call pCKinematicsAnimated__PlayCycle
		mov result, eax
	};
	
	POP_REG(ecx)

	return result;
}

unsigned long CKinematicsAnimated__PlayCycleEx(unsigned long pClass,unsigned long unk1,unsigned long MotionID,int unknown, DWORD pointer1, DWORD pObject,DWORD unk2)
{
	PUSH_REG(ecx)

	unsigned long result = 0;
	
	if(pObject != 0)
	{
		if(MotionID != 0xA0007)
		{
			// get object id
			unsigned short objectid = 0;

			for(int i = 0;i < 0xFFFF;i++)
			{
				if(!g_pGameLevel->ObjectList.objects[i]) continue;

				if((*(DWORD*)((DWORD)g_pGameLevel->ObjectList.objects[i] + 0x90) + 0xB0) == pClass) 
				{
					objectid = i;
					break;
				}
			}
			
			// Custom sync
			if(CustomSyncData_Entity[objectid])
			{				
				SendCycleExPacket(objectid,unk1,MotionID);
			}
		}
	}
	
	_asm
	{
		push unk2
		push pObject
		push pointer1
		push unknown
		push MotionID
		push unk1
		mov ecx, pClass
		call pCKinematicsAnimated__PlayCycleEx
		mov result, eax
	};
	
	POP_REG(ecx)

	return result;
}

void CLevel__cl_Process_Motion(NET_Packet& pack)
{
	LogHandle->Write("CLevel__cl_Process_Motion");
	if(HookHandle->IsServer() == 1) return;

	unsigned short objectid;
	unsigned char type;
	unsigned long MotionID;
	unsigned long unk;

	pack.r_u16(objectid);
	pack.r_u8(type);
	if(type == 2) pack.r(&unk,sizeof(unsigned long));
	pack.r(&MotionID,sizeof(unsigned long));

	
	if(g_pGameLevel->ObjectList.objects[objectid] != 0) 
	{
		if(type == 1) HookHandle->PlayCycle((DWORD)g_pGameLevel->ObjectList.objects[objectid],MotionID);
		else if(type == 2) HookHandle->PlayCycleEx((DWORD)g_pGameLevel->ObjectList.objects[objectid],unk,MotionID);
	}
}
