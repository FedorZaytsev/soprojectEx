/*
*	S.T.A.L.K.E.R. Online - hook base class
*	Developers:
*		009 (Михайлов Алексей)
*/

#include "hook.h"

#include "../shared/log.h"

// extern
extern CLog* LogHandle;

void CHook::Call(unsigned long from,unsigned long to)
{
	// unprotect
	DWORD oldp;
	if(VirtualProtect((LPVOID)from,5,PAGE_EXECUTE_READWRITE, &oldp))
	{
		*(unsigned char*)(from) = 0xE8;
		*(unsigned long*)(from + 1) = (to - (from + 5));
	}
}

void CHook::JmpEx(unsigned char prefix,unsigned long from,unsigned long to)
{
	// unprotect
	DWORD oldp;
	if(VirtualProtect((LPVOID)from,5,PAGE_EXECUTE_READWRITE, &oldp))
	{
		*(unsigned char*)(from) = prefix;
		*(unsigned long*)(from + 1) = (to - (from + 5));
	}
}

void CHook::Jmp(unsigned long from,unsigned long to)
{
	// unprotect
	DWORD oldp;
	if(VirtualProtect((LPVOID)from,5,PAGE_EXECUTE_READWRITE, &oldp))
	{
		*(unsigned char*)(from) = 0xE9;
		*(unsigned long*)(from + 1) = (to - (from + 5));
	}
}

void CHook::Byte(unsigned long addr,unsigned int size,unsigned char byte)
{
	// unprotect
	DWORD oldp;
	if(VirtualProtect((LPVOID)addr,size,PAGE_EXECUTE_READWRITE, &oldp))
	{
		for(unsigned int i = 0;i < size;i++) *(unsigned char*)(addr + i) = byte;
	}
}

void CHook::Address(unsigned long addr,unsigned long data)
{
	unsigned char bytes[4];
	bytes[0] = (unsigned char)(data);
	bytes[1] = (unsigned char)(data >> 8);
	bytes[2] = (unsigned char)(data >> 16);
	bytes[3] = (unsigned char)(data >> 24);
	// set offset
	Byte(((unsigned long)addr + 0),1,bytes[0]);
	Byte(((unsigned long)addr + 1),1,bytes[1]);
	Byte(((unsigned long)addr + 2),1,bytes[2]);
	Byte(((unsigned long)addr + 3),1,bytes[3]);
}

void CHook::JoinInClassFtable(unsigned long addr,unsigned long function,unsigned char retn)
{
	/*
	our function in asm:
	
	008		edi
	004		class
	000		return point
	-004	arg0...

	000 push ecx	// now this is class
	004 push edi
	008 add esp, 8
	000 pop ecx		// now this is return point
	-04 sub esp, 8
	004 pop edi		// now this is class
	000 add esp, 4
	-04 push edi
	000 sub esp, 8
	008 pop edi		// edi = orig_edi
	004 add esp, 4
	000 call func
	000 add esp,4
	-04 push ecx	// write return point
	000 retn 14h

	*/

	// alloc memory
	void* func_mem = malloc(33);
	// write instructions:
	Byte(((unsigned long)func_mem + 0),1,0x51);			// push ecx
	Byte(((unsigned long)func_mem + 1),1,0x57);			// push edi
	Byte(((unsigned long)func_mem + 2),1,0x83);			// add esp, 8
	Byte(((unsigned long)func_mem + 3),1,0xC4);
	Byte(((unsigned long)func_mem + 4),1,0x8);
	Byte(((unsigned long)func_mem + 5),1,0x59);			// pop ecx
	Byte(((unsigned long)func_mem + 6),1,0x83);			// sub esp, 8
	Byte(((unsigned long)func_mem + 7),1,0xEC);
	Byte(((unsigned long)func_mem + 8),1,0x8);
	Byte(((unsigned long)func_mem + 9),1,0x5F);			// pop edi
	Byte(((unsigned long)func_mem + 10),1,0x83);		// add esp, 4
	Byte(((unsigned long)func_mem + 11),1,0xC4);
	Byte(((unsigned long)func_mem + 12),1,0x4);
	Byte(((unsigned long)func_mem + 13),1,0x57);		// push edi
	Byte(((unsigned long)func_mem + 14),1,0x83);		// sub esp, 8
	Byte(((unsigned long)func_mem + 15),1,0xEC);
	Byte(((unsigned long)func_mem + 16),1,0x8);
	Byte(((unsigned long)func_mem + 17),1,0x5F);		// pop edi
	Byte(((unsigned long)func_mem + 18),1,0x83);		// add esp, 4
	Byte(((unsigned long)func_mem + 19),1,0xC4);
	Byte(((unsigned long)func_mem + 20),1,0x4);
	Call(((unsigned long)func_mem + 21),function);		// call func
	Byte(((unsigned long)func_mem + 26),1,0x83);		// add esp, 4
	Byte(((unsigned long)func_mem + 27),1,0xC4);
	Byte(((unsigned long)func_mem + 28),1,0x4);
	Byte(((unsigned long)func_mem + 29),1,0x51);		// push ecx
	Byte(((unsigned long)func_mem + 30),1,0xC2);		// retn 14h
	Byte(((unsigned long)func_mem + 31),1,retn);
	Byte(((unsigned long)func_mem + 32),1,0x0);

	// set call of our small function
	Address(addr,(unsigned long)func_mem);
}

void CHook::JoinInClassFtableEx(unsigned long addr,unsigned long function,unsigned char retn,unsigned long& old_function)
{
	/*
	our function in asm:
	
	008		edi
	004		class
	000		return point
	-004	arg0...

	000 push ecx	// now this is class
	004 push edi
	008 add esp, 8
	000 pop ecx		// now this is return point
	-04 sub esp, 8
	004 pop edi		// now this is class
	000 add esp, 4
	-04 push edi
	000 sub esp, 8
	008 pop edi		// edi = orig_edi
	004 add esp, 4
	000 call func
	000 add esp,4
	-04 push ecx	// write return point
	000 retn 14h

	*/

	// alloc memory
	// copy old func
	
	old_function = (*(BYTE*)(addr + 3) << 24) + (*(BYTE*)(addr + 2) << 16) + (*(BYTE*)(addr + 1) << 8) + *(BYTE*)(addr + 0);

	void* func_mem = malloc(33);
	// write instructions:
	Byte(((unsigned long)func_mem + 0),1,0x51);			// push ecx
	Byte(((unsigned long)func_mem + 1),1,0x57);			// push edi
	Byte(((unsigned long)func_mem + 2),1,0x83);			// add esp, 8
	Byte(((unsigned long)func_mem + 3),1,0xC4);
	Byte(((unsigned long)func_mem + 4),1,0x8);
	Byte(((unsigned long)func_mem + 5),1,0x59);			// pop ecx
	Byte(((unsigned long)func_mem + 6),1,0x83);			// sub esp, 8
	Byte(((unsigned long)func_mem + 7),1,0xEC);
	Byte(((unsigned long)func_mem + 8),1,0x8);
	Byte(((unsigned long)func_mem + 9),1,0x5F);			// pop edi
	Byte(((unsigned long)func_mem + 10),1,0x83);		// add esp, 4
	Byte(((unsigned long)func_mem + 11),1,0xC4);
	Byte(((unsigned long)func_mem + 12),1,0x4);
	Byte(((unsigned long)func_mem + 13),1,0x57);		// push edi
	Byte(((unsigned long)func_mem + 14),1,0x83);		// sub esp, 8
	Byte(((unsigned long)func_mem + 15),1,0xEC);
	Byte(((unsigned long)func_mem + 16),1,0x8);
	Byte(((unsigned long)func_mem + 17),1,0x5F);		// pop edi
	Byte(((unsigned long)func_mem + 18),1,0x83);		// add esp, 4
	Byte(((unsigned long)func_mem + 19),1,0xC4);
	Byte(((unsigned long)func_mem + 20),1,0x4);
	Call(((unsigned long)func_mem + 21),function);		// call func
	Byte(((unsigned long)func_mem + 26),1,0x83);		// add esp, 4
	Byte(((unsigned long)func_mem + 27),1,0xC4);
	Byte(((unsigned long)func_mem + 28),1,0x4);
	Byte(((unsigned long)func_mem + 29),1,0x51);		// push ecx
	Byte(((unsigned long)func_mem + 30),1,0xC2);		// retn 14h
	Byte(((unsigned long)func_mem + 31),1,retn);
	Byte(((unsigned long)func_mem + 32),1,0x0);

	// set call of our small function
	Address(addr,(unsigned long)func_mem);
}

void CHook::CreateSwitchTable(unsigned long* locations,unsigned int locations_count,unsigned char* jump_table,unsigned int jump_table_size,unsigned long addr_loc,unsigned long addr_table,unsigned long addr_table_size)
{
	// create data
	void* loc_data = malloc(locations_count * 4);
	void* table_data = malloc(jump_table_size);
	// write locations
	for(unsigned int i = 0;i < locations_count;i++)	Address(((DWORD)loc_data + i*4),locations[i]);
	// write table
	for(unsigned int i = 0;i < jump_table_size;i++)	Byte(((DWORD)table_data + i),1,jump_table[i]);
	// change orig locations addr
	Address(addr_loc,(DWORD)loc_data);
	// change orig jump table addr
	Address(addr_table,(DWORD)table_data);
	// change orig jump table size
	Byte(addr_table_size,1,jump_table_size);
}

void CHook::LinkAddresses()
{
	DWORD tmp;
	// link memory
	Memory = (xrMemory*)(GetProcAddress(CoreOffset,"?Memory@@3VxrMemory@@A"));
	// locator api
	while((tmp = *(DWORD*)GetProcAddress(CoreOffset,"?xr_FS@@3PAVCLocatorAPI@@A")) == NULL) Sleep(5);
	xr_FS = (CLocatorAPI*)(tmp);
	// link console
	while((tmp = *(DWORD*)GetProcAddress(EngineOffset,"?Console@@3PAVCConsole@@A")) == NULL) Sleep(5);
	Console = (CConsole*)(tmp);
	// link string container
	while((tmp = *(DWORD*)GetProcAddress(CoreOffset,"?g_pStringContainer@@3PAVstr_container@@A")) == NULL) Sleep(5);
	g_pStringContainer = (str_container*)(tmp);
}