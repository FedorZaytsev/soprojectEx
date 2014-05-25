/*
*	S.T.A.L.K.E.R.- IGame_Level class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "CObjectList.h"
#include "CObjectSpace.h"

class IGame_Level
{
public:
	IGame_Level();
	~IGame_Level();

	DLL_Pure * dwDLL_Pure; // link on DLL_Pure // 0x0
	unsigned long Unknown1; // unknown link // 0x4
	unsigned long Unknown2; // unknown link // 0x8
	unsigned long Unknown3; // unknown link // 0xC
	unsigned long dwIInputReceiver; // link on IInputReceiver // 0x10
	unsigned long dwpureRender; // link on pureRender // 0x14
	pureFrame * dwpureFrame; // link on pureFrame // 0x18
	IEventReceiver * dwIEventReceiver; // link on IEventReceiver // 0x1C
	CObject* pCurrentEntity; // unknown link // 0x20
	unsigned long Unknown5; // unknown link // 0x24
	unsigned long Unknown6; // unknown link // 0x28
	unsigned long Unknown7; // unknown link // 0x2C
	unsigned long Unknown8; // unknown link // 0x30
	unsigned long Unknown9; // unknown link // 0x34
	unsigned long Unknown10; // unknown link // 0x38
	unsigned long Unknown11; // unknown link // 0x3C
	unsigned long Unknown12; // unknown link // 0x40
	unsigned long Unknown13; // unknown link // 0x44
	unsigned long Unknown14; // unknown link // 0x48
	CObjectList ObjectList; // ObjectList - not link // 0x4C
	// size - 0x40048 = 262216
	CObjectSpace ObjectSpace; // ObjectSpace - not link // 0x40094
	// size - 0x68 = 104
	unsigned long Unknown15; // unknown // 0x400FC
	unsigned long Unknown16; // unknown // 0x40100
/*
	unsigned long Unknown16; // unknown // 0x40104
	unsigned long Unknown16; // unknown // 0x40108
	unsigned long Unknown16; // unknown // 0x4010C
	unsigned long dwIPureClient; // link on IPureClient // 0x40110
	char pad[0x8473];
	unsigned long dwmessage_filter; // 0x48584
	unsigned long dwNeed; // 0x486F0
	unsigned long dwCriticalSection; // 0x4849C
*/
};