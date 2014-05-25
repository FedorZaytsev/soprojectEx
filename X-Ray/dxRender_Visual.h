/*
*	S.T.A.L.K.E.R.- dxRender_Visual class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

class dxRender_Visual
{
public:
	dxRender_Visual();
	~dxRender_Visual();

	unsigned long ftable;		// 0x0
	unsigned long visual_type;	// 0x4
	_box3<float> box;			// 0x8, 0xC, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28
	float unknown1;				// 0x2C
	unsigned long unknown2[5];	// 0x30, 0x34, 0x38, 0x3C, 0x40
	unsigned long Visuel_4_type_info[3];	// 0x44, 0x48, 0x4C
	unsigned long unknown;		// 0x50
};