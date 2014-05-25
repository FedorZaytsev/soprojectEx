/*
*	S.T.A.L.K.E.R.- CObjectList class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "CObject.h"

class __declspec(dllimport) CObjectList
{
public:
	CObjectList();
	~CObjectList();

	CObject * Create(char const *);
	void Destroy(CObject *);
	unsigned int o_count(void);

	CObject* objects[65535]; // 0x0, size 0xFFFF 
	unsigned long unknown1; // 0x3FFFC
	unsigned long unknown2; // 0x40000
	int unknown22; // 0x40004
	unsigned long object_count; // 0x10006
	int unknown3; // 0x4000A
	unsigned long unknown4; // 0x4000C
	unsigned long unknown5; // 0x40010
	unsigned long unknown6; // 0x40014
	unsigned long unknown7; // 0x40018
	unsigned long unknown8; // 0x4001C
	unsigned long unknown9; // 0x40020
	unsigned long unknown10; // 0x40024
	unsigned long unknown11; // 0x40028
	unsigned long unknown12; // 0x4002C
	unsigned long unknown13; // 0x40030
	unsigned long unknown14; // 0x40034
	unsigned long unknown15; // 0x40038
	unsigned long unknown16; // 0x4003C
	unsigned long unknown17; // 0x40040
	unsigned long unknown18; // 0x40044
};