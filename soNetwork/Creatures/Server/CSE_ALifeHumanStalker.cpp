/*
*	S.T.A.L.K.E.R. Online - Stalkers sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

//#define CSE_ALIFE_HUMAN_STALKER_DEBUG

#include "../../../shared/hook.h"

#ifdef CSE_ALIFE_HUMAN_STALKER_DEBUG
	#include "../../../shared/log.h"
	extern CLog* LogHandle;
#endif

struct CSE_ALifeHumanStalker_sync_buffer
{
	FLOAT   position[3];
	FLOAT   direction[3];
	FLOAT	heading;
	FLOAT	head_orientation[2];
	WORD	CurrentWeapon;
};

extern void*	CustomSyncData_Entity[0xFFFF];		// 0xFFFF - max of Entitys in game
extern DWORD	pCSE_ALifeHumanStalker__UPDATE_Write;
extern DWORD	pCSE_ALifeHumanStalker__UPDATE_Read;
extern DWORD	pUPDATE_Write_call_address;
extern DWORD	pUPDATE_Read_call_address;
extern DWORD	gGameOffset;
extern BYTE		PatchVersion;

void CSE_ALifeHumanStalker__UPDATE_Write(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	if(orig_reg != pUPDATE_Write_call_address) // called not from xrServer::SyncAllCreautres
	{
		_asm
		{
			push pack
			mov ecx, pClass
			call pCSE_ALifeHumanStalker__UPDATE_Write
		}

		POP_REG(ecx)
		return;
	}
	
	pClass -= 0x60;

	unsigned short objectid = *(unsigned short*)(pClass + 0x8A);
	CSE_ALifeHumanStalker_sync_buffer* sync_buffer = (CSE_ALifeHumanStalker_sync_buffer*)CustomSyncData_Entity[objectid];

	// pack data
	pack->w(&sync_buffer->position,0xC);
	pack->w(&sync_buffer->direction,0xC);
	pack->w(&sync_buffer->heading,0x4);
	pack->w(&sync_buffer->head_orientation,0x8);
	pack->w_u16(sync_buffer->CurrentWeapon);

#ifdef CSE_ALIFE_HUMAN_STALKER_DEBUG

	LogHandle->Write("CSE_ALifeHumanStalker::UPDATE_Write(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,sync_buffer->position[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,sync_buffer->direction[i]);
	LogHandle->Write("heading = %f",sync_buffer->heading);
	for(int i = 0;i < 2;i++) LogHandle->Write("head_orientation[%d] = %f",i,sync_buffer->head_orientation[i]);
	LogHandle->Write("CurrentWeapon = %d",sync_buffer->CurrentWeapon);

	LogHandle->Write("}");
#endif
	
	POP_REG(ecx)
}

void CSE_ALifeHumanStalker__UPDATE_Read(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)
	
	if(orig_reg != pUPDATE_Read_call_address) // called not from xrServer::Process_update
	{
		_asm
		{
			push pack
			mov ecx, pClass
			call pCSE_ALifeHumanStalker__UPDATE_Read
		}

		POP_REG(ecx)
		return;
	}
	
	pClass -= 0x60;

	unsigned short objectid = *(unsigned short*)(pClass + 0x8A);
	CSE_ALifeHumanStalker_sync_buffer* sync_buffer = (CSE_ALifeHumanStalker_sync_buffer*)CustomSyncData_Entity[objectid];

	// create sync buffer
	if(!sync_buffer) 
	{
		sync_buffer = new CSE_ALifeHumanStalker_sync_buffer;
		CustomSyncData_Entity[objectid] = sync_buffer;
	}

	// pack data
	pack->r(&sync_buffer->position,0xC);
	pack->r(&sync_buffer->direction,0xC);
	pack->r(&sync_buffer->heading,0x4);
	pack->r(&sync_buffer->head_orientation,0x8);
	pack->r_u16(sync_buffer->CurrentWeapon);

#ifdef CSE_ALIFE_HUMAN_STALKER_DEBUG

	LogHandle->Write("CSE_ALifeHumanStalker::UPDATE_Read(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,sync_buffer->position[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,sync_buffer->direction[i]);
	LogHandle->Write("heading = %f",sync_buffer->heading);
	for(int i = 0;i < 2;i++) LogHandle->Write("head_orientation[%d] = %f",i,sync_buffer->head_orientation[i]);
	LogHandle->Write("CurrentWeapon = %d",sync_buffer->CurrentWeapon);

	LogHandle->Write("}");
#endif
	
	POP_REG(ecx)
}