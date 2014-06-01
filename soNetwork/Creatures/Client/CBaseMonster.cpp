/*
*	S.T.A.L.K.E.R. Online - CBaseMonster sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

//#define CBASEMONSTER_DEBUG

#include "../../../shared/hook.h"

#ifdef CBASEMONSTER_DEBUG
	#include "../../../shared/log.h"
	extern CLog* LogHandle;
#endif

extern DWORD gGameOffset;

void CBaseMonster__NET_Export(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	DWORD   pMovementManager = *(DWORD*)(pClass + 0x380);
	DWORD   pControlAnimation = *(DWORD*)(pClass + 0x6DC);
	DWORD   pControlMovement = *(DWORD*)(pClass + 0x6E0);
	DWORD   pControlDirection = *(DWORD*)(pClass + 0x6E8);
	
	FLOAT   position[3];
	FLOAT   direction[3];
	BYTE	animation;
	FLOAT	heading;
	
	memcpy(&position,(void*)(pClass + 0x80),0xC);
	memcpy(&direction,(void*)(pClass + 0x70),0xC);
	animation = *(BYTE*)(pControlAnimation + 0xF0);
	heading = *(FLOAT*)(pControlDirection + 0x28);
	
	pack->w(&position,0xC);
	pack->w(&direction,0xC);
	pack->w(&animation,0x1);
	pack->w(&heading,0x4);

	#ifdef CBASEMONSTER_DEBUG

	LogHandle->Write("CBaseMonster::NET_Export(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");

	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	LogHandle->Write("animation = %d",animation);
	LogHandle->Write("heading = %f",heading);

	LogHandle->Write("}");

	#endif

	POP_REG(ecx)
}

void CBaseMonster__NET_Import(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)
	
	DWORD   pMovementManager = *(DWORD*)(pClass + 0x380);
	DWORD   pControlAnimation = *(DWORD*)(pClass + 0x6DC);
	DWORD   pControlMovement = *(DWORD*)(pClass + 0x6E0);
	DWORD   pControlDirection = *(DWORD*)(pClass + 0x6E8);

	FLOAT	m_state_holder_state[33];
	FLOAT   position[3];
	FLOAT   direction[3];
	BYTE	animation;
	FLOAT	heading;

	pack->r(&position,0xC);
	pack->r(&direction,0xC);
	pack->r(&animation,0x1);
	pack->r(&heading,0x4);

	memcpy((void*)(pClass + 0x80),&position,0xC);
	memcpy((void*)(pClass + 0x70),&direction,0xC);
	*(BYTE*)(pControlAnimation + 0xF0) = animation;
	*(FLOAT*)(pControlDirection + 0x28) = heading;
	
	memset(&m_state_holder_state,0,33 * 4);
	m_state_holder_state[12] = m_state_holder_state[15] = position[0];
	m_state_holder_state[13] = m_state_holder_state[16] = position[1];
	m_state_holder_state[14] = m_state_holder_state[17] = position[2];

#ifdef CBASEMONSTER_DEBUG

	LogHandle->Write("CBaseMonster::NET_Import(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	LogHandle->Write("animation = %d",animation);
	LogHandle->Write("heading = %f",heading);

	LogHandle->Write("}");
#endif

	DWORD	pEntityAlive__PHGetSyncItem = *(DWORD*)(*(DWORD*)pClass + 0x1C0);
	DWORD	pPHCharacter__set_State;
	DWORD	PHCharacter;
	void*	pointer = &m_state_holder_state;

	if(pEntityAlive__PHGetSyncItem)
	{
		// get sync item
		_asm
		{
			push 0
			mov ecx, pClass
			call pEntityAlive__PHGetSyncItem
			mov PHCharacter, eax
		};

		if(PHCharacter)
		{
			pPHCharacter__set_State = *(DWORD*)(*(DWORD*)PHCharacter + 0xC);

			if(pPHCharacter__set_State)
			{
				// set state
				_asm
				{
					push pointer
					mov ecx, PHCharacter
					call pPHCharacter__set_State
				};
			}
		}
	}	

	POP_REG(ecx)
}