/*
*	S.T.A.L.K.E.R. Online - Stalker sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

//#define CAI_STALKER_DEBUG

#include "../../../shared/hook.h"

#ifdef CAI_STALKER_DEBUG
	#include "../shared/log.h"
	extern CLog* LogHandle;
#endif

void CAI_Stalker__NET_Export(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	FLOAT	unknown[3];
	FLOAT	unknown2[3];
	FLOAT	direction[3];
	FLOAT	position[3];
	FLOAT	rotation[3];
	FLOAT	HeadOrientation[2];
	WORD	CurrentWeapon;

	DWORD	pMovementManager = *(DWORD*)(pClass + 0x5F8);
	DWORD	pInventory = *(DWORD*)(pClass + 0x4D4);
	
	// copy data
	memcpy(&unknown,(void*)(pClass + 0x50),0xC);
	memcpy(&unknown2,(void*)(pClass + 0x60),0xC);
	memcpy(&direction,(void*)(pClass + 0x70),0xC);
	memcpy(&position,(void*)(pClass + 0x80),0xC);
	memcpy(&rotation,(void*)(pMovementManager + 0x10),0xC);
	HeadOrientation[0] = *(float*)(pMovementManager + 0x16C);
	HeadOrientation[1] = *(float*)(pMovementManager + 0x170);
	if(pInventory) CurrentWeapon = *(unsigned short*)(pInventory + 0x40);
	else CurrentWeapon = 0;
	
	// pack data
	pack->w(&unknown,0xC);
	pack->w(&unknown2,0xC);
	pack->w(&direction,0xC);
	pack->w(&position,0xC);
	pack->w(&rotation,0xC);
	pack->w_float(HeadOrientation[0]);
	pack->w_float(HeadOrientation[1]);
	pack->w_u16(CurrentWeapon);

#ifdef CAI_STALKER_DEBUG

	LogHandle->Write("CAI_Stalker::NET_Export(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");

	for(int i = 0;i < 3;i++) LogHandle->Write("unknown[%d] = %f",i,unknown[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("unknown2[%d] = %f",i,unknown2[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("rotation[%d] = %f",i,rotation[i]);
	LogHandle->Write("HeadOrientation[0] = %f",HeadOrientation[0]);
	LogHandle->Write("HeadOrientation[1] = %f",HeadOrientation[1]);
	LogHandle->Write("CurrentWeapon = %d",CurrentWeapon);

	LogHandle->Write("}");
#endif

	POP_REG(ecx)
}

void CAI_Stalker__NET_Import(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	FLOAT	unknown[3];
	FLOAT	unknown2[3];
	FLOAT	direction[3];
	FLOAT	position[3];
	FLOAT	rotation[3];
	FLOAT	HeadOrientation[2];
	WORD	CurrentWeapon;

	DWORD	pMovementManager = *(DWORD*)(pClass + 0x5F8);
	DWORD	pInventory = *(DWORD*)(pClass + 0x4D4);
	
	// unpack data
	pack->r(&unknown,0xC);
	pack->r(&unknown2,0xC);
	pack->r(&direction,0xC);
	pack->r(&position,0xC);
	pack->r(&rotation,0xC);
	pack->r_float(HeadOrientation[0]);
	pack->r_float(HeadOrientation[1]);
	pack->r_u16(CurrentWeapon);

	// copy data
	memcpy((void*)(pClass + 0x50),&unknown,0xC);
	memcpy((void*)(pClass + 0x60),&unknown2,0xC);
	memcpy((void*)(pClass + 0x70),&direction,0xC);
	memcpy((void*)(pClass + 0x80),&position,0xC);
	memcpy((void*)(pMovementManager + 0x10),&rotation,0xC);
	*(float*)(pMovementManager + 0x16C) = HeadOrientation[0];
	*(float*)(pMovementManager + 0x170) = HeadOrientation[1];
	if(pInventory) *(unsigned short*)(pInventory + 0x40) = CurrentWeapon;
	// collision apply
	memcpy((void*)(pClass + 0x18),&position,0xC);
	
#ifdef CAI_STALKER_DEBUG

	LogHandle->Write("CAI_Stalker::NET_Import(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");

	for(int i = 0;i < 3;i++) LogHandle->Write("unknown[%d] = %f",i,unknown[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("unknown2[%d] = %f",i,unknown2[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("rotation[%d] = %f",i,rotation[i]);
	LogHandle->Write("HeadOrientation[0] = %f",HeadOrientation[0]);
	LogHandle->Write("HeadOrientation[1] = %f",HeadOrientation[1]);
	LogHandle->Write("CurrentWeapon = %d",CurrentWeapon);

	LogHandle->Write("}");
#endif

	((CObject*)(pClass))->setVisible(1);
	((CObject*)(pClass))->setEnabled(1);
	
	POP_REG(ecx)
}