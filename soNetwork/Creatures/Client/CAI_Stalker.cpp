/*
*	S.T.A.L.K.E.R. Online - Stalker sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

//#define CAI_STALKER_DEBUG

#include "../../../shared/hook.h"

#ifdef CAI_STALKER_DEBUG
	#include "../../../shared/log.h"
	extern CLog* LogHandle;
#endif

void CAI_Stalker__NET_Export(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)
	
	DWORD   pMovementManager = *(DWORD*)(pClass + 0x5F8);
	DWORD   pAnimationManager = *(DWORD*)(pClass + 0x5EC);
	DWORD	pInventory = *(DWORD*)(pClass + 0x4D4);
	
	FLOAT   position[3];
	FLOAT   direction[3];
	FLOAT	heading;
	FLOAT	head_orientation[2];
	WORD	CurrentWeapon;

	memcpy(&position,(void*)(pClass + 0x80),0xC);
	memcpy(&direction,(void*)(pClass + 0x70),0xC);
	heading = *(FLOAT*)(pMovementManager + 0x14);
	memcpy(&head_orientation,(void*)(pMovementManager + 0x16C),0x8);
	if(pInventory) CurrentWeapon = *(unsigned short*)(pInventory + 0x40);
	else CurrentWeapon = 0;
	
	pack->w(&position,0xC);
	pack->w(&direction,0xC);
	pack->w(&heading,0x4);
	pack->w(&head_orientation,0x8);
	pack->w_u16(CurrentWeapon);
	

#ifdef CAI_STALKER_DEBUG

	LogHandle->Write("CAI_Stalker::NET_Export(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");

	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);
	LogHandle->Write("heading = %f",heading);
	for(int i = 0;i < 2;i++) LogHandle->Write("head_orientation[%d] = %f",i,head_orientation[i]);
	LogHandle->Write("CurrentWeapon = %d",CurrentWeapon);

	LogHandle->Write("}");
#endif

	POP_REG(ecx)
}

void CAI_Stalker__NET_Import(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)
		
	DWORD   pMovementManager = *(DWORD*)(pClass + 0x5F8);
	DWORD   pAnimationManager = *(DWORD*)(pClass + 0x5EC);
	DWORD	pInventory = *(DWORD*)(pClass + 0x4D4);
	
	FLOAT	m_state_holder_state[33];
	FLOAT   position[3];
	FLOAT   direction[3];
	FLOAT	heading;
	FLOAT	head_orientation[2];
	WORD	CurrentWeapon;
	
	pack->r(&position,0xC);
	pack->r(&direction,0xC);
	pack->r(&heading,0x4);
	pack->r(&head_orientation,0x8);
	pack->r_u16(CurrentWeapon);

	memcpy((void*)(pClass + 0x80),&position,0xC);
	memcpy((void*)(pClass + 0x70),&direction,0xC);
	*(FLOAT*)(pMovementManager + 0x14) = heading;
	memcpy((void*)(pMovementManager + 0x16C),&head_orientation,0x8);
	if(pInventory) *(unsigned short*)(pInventory + 0x40) = CurrentWeapon;
	
	memset(&m_state_holder_state,0,33 * 4);
	m_state_holder_state[12] = m_state_holder_state[15] = position[0];
	m_state_holder_state[13] = m_state_holder_state[16] = position[1];
	m_state_holder_state[14] = m_state_holder_state[17] = position[2];
	
#ifdef CAI_STALKER_DEBUG

	LogHandle->Write("CAI_Stalker::NET_Import(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);
	LogHandle->Write("heading = %f",heading);
	for(int i = 0;i < 2;i++) LogHandle->Write("head_orientation[%d] = %f",i,head_orientation[i]);
	LogHandle->Write("CurrentWeapon = %d",CurrentWeapon);

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

	((CObject*)(pClass))->setVisible(1);
	((CObject*)(pClass))->setEnabled(1);
	
	POP_REG(ecx)
}