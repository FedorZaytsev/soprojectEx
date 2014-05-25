/*
*	S.T.A.L.K.E.R. Online - Trader sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

//#define CSE_ALIFE_TRADER_DEBUG

#include "../../../shared/hook.h"

#ifdef CSE_ALIFE_TRADER_DEBUG
	#include "../../../shared/log.h"
	extern CLog* LogHandle;
#endif

struct CSE_ALifeTrader_sync_buffer
{
	FLOAT	unknown[3];
	FLOAT	unknown2[3];
	FLOAT	direction[3];
	FLOAT	position[3];
};

extern void*	CustomSyncData_Entity[0xFFFF];		// 0xFFFF - max of Entitys in game
extern DWORD	pCSE_ALifeTrader__UPDATE_Write;
extern DWORD	pCSE_ALifeTrader__UPDATE_Read;
extern DWORD	pUPDATE_Write_call_address;
extern DWORD	pUPDATE_Read_call_address;
extern DWORD	gGameOffset;
extern BYTE		PatchVersion;

void CSE_ALifeTrader__UPDATE_Write(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	if(orig_reg != pUPDATE_Write_call_address) // called not from xrServer::SyncAllCreautres
	{
		_asm
		{
			push pack
			mov ecx, pClass
			call pCSE_ALifeTrader__UPDATE_Write
		}

		POP_REG(ecx)
		return;
	}

	unsigned short objectid = *(unsigned short*)(pClass + 0x2A);
	CSE_ALifeTrader_sync_buffer* sync_buffer = (CSE_ALifeTrader_sync_buffer*)CustomSyncData_Entity[objectid];
	
	// pack data
	pack->w(&sync_buffer->unknown,0xC);
	pack->w(&sync_buffer->unknown2,0xC);
	pack->w(&sync_buffer->direction,0xC);
	pack->w(&sync_buffer->position,0xC);

#ifdef CSE_ALIFE_TRADER_DEBUG

	LogHandle->Write("CSE_ALifeTrader::UPDATE_Write(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("unknown[%d] = %f",i,sync_buffer->unknown[i]);
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("unknown2[%d] = %f",i,sync_buffer->unknown2[i]);
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,sync_buffer->direction[i]);
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,sync_buffer->position[i]);

	LogHandle->Write("}");
#endif

	POP_REG(ecx)
}

void CSE_ALifeTrader__UPDATE_Read(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	if(orig_reg != pUPDATE_Read_call_address) // called not from xrServer::Process_update
	{
		_asm
		{
			push pack
			mov ecx, pClass
			call pCSE_ALifeTrader__UPDATE_Read
		}

		POP_REG(ecx)
		return;
	}

	unsigned short objectid = *(unsigned short*)(pClass + 0x2A);
	CSE_ALifeTrader_sync_buffer* sync_buffer = (CSE_ALifeTrader_sync_buffer*)CustomSyncData_Entity[objectid];

	// create sync buffer
	if(!sync_buffer) 
	{
		sync_buffer = new CSE_ALifeTrader_sync_buffer;
		CustomSyncData_Entity[objectid] = sync_buffer;
	}
	
	// unpack data
	pack->r(&sync_buffer->unknown,0xC);
	pack->r(&sync_buffer->unknown2,0xC);
	pack->r(&sync_buffer->direction,0xC);
	pack->r(&sync_buffer->position,0xC);

#ifdef CSE_ALIFE_TRADER_DEBUG

	LogHandle->Write("CSE_ALifeTrader::UPDATE_Read(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("unknown[%d] = %f",i,sync_buffer->unknown[i]);
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("unknown2[%d] = %f",i,sync_buffer->unknown2[i]);
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,sync_buffer->direction[i]);
	for(unsigned long i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,sync_buffer->position[i]);

	LogHandle->Write("}");
#endif

	POP_REG(ecx)
}