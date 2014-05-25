/*
*	S.T.A.L.K.E.R. Online - Crow sync
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <stdlib.h>

//#define CAI_CROW_DEBUG

#include "../../../shared/hook.h"

#ifdef CAI_CROW_DEBUG
	#include "../shared/log.h"
	extern CLog* LogHandle;
#endif

void CAI_Crow__NET_Export(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)

	FLOAT	unknown[3];
	FLOAT	unknown2[3];
	FLOAT	direction[3];
	FLOAT	position[3];

	WORD	objectid = ((CObject*)pClass)->ID();
	
	// copy data
	memcpy(&unknown,(void*)(pClass + 0x50),0xC);
	memcpy(&unknown2,(void*)(pClass + 0x60),0xC);
	memcpy(&direction,(void*)(pClass + 0x70),0xC);
	memcpy(&position,(void*)(pClass + 0x80),0xC);

	// pack data
	pack->w(&unknown,0xC);
	pack->w(&unknown2,0xC);
	pack->w(&direction,0xC);
	pack->w(&position,0xC);
	
#ifdef CAI_CROW_DEBUG

	LogHandle->Write("CAI_Crow::NET_Export(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(int i = 0;i < 3;i++) LogHandle->Write("unknown[%d] = %f",i,unknown[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("unknown2[%d] = %f",i,unknown2[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);

	LogHandle->Write("}");
#endif

	POP_REG(ecx)
}

void CAI_Crow__NET_Import(DWORD pClass,NET_Packet* pack)
{
	PUSH_REG(ecx)
	
	FLOAT	unknown[3];
	FLOAT	unknown2[3];
	FLOAT	direction[3];
	FLOAT	position[3];

	// unpack data
	pack->r(&unknown,0xC);
	pack->r(&unknown2,0xC);
	pack->r(&direction,0xC);
	pack->r(&position,0xC);

	// copy data
	memcpy((void*)(pClass + 0x50),&unknown,0xC);
	memcpy((void*)(pClass + 0x60),&unknown2,0xC);
	memcpy((void*)(pClass + 0x70),&direction,0xC);
	memcpy((void*)(pClass + 0x80),&position,0xC);
	// collision apply
	memcpy((void*)(pClass + 0x18),&position,0xC);

#ifdef CAI_CROW_DEBUG

	LogHandle->Write("CAI_Crow::NET_Import(0x%X,0x%X)",pClass,pack);
	LogHandle->Write("{");
	
	for(int i = 0;i < 3;i++) LogHandle->Write("unknown[%d] = %f",i,unknown[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("unknown2[%d] = %f",i,unknown2[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("direction[%d] = %f",i,direction[i]);
	for(int i = 0;i < 3;i++) LogHandle->Write("position[%d] = %f",i,position[i]);

	LogHandle->Write("}");
#endif

	((CObject*)(pClass))->setVisible(1);
	((CObject*)(pClass))->setEnabled(1);
	
	POP_REG(ecx)
}