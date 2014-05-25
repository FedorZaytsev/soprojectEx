/*
*	S.T.A.L.K.E.R.- NET_Packet class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#pragma once

#include "utils.h"

class __declspec(dllimport) NET_Packet
{
public:
	NET_Packet(void);
	// functions
	// write
	void w(void const *source, unsigned int size);
	void write_start(void);
	void w_begin(unsigned short id);
	int w_seek(int pos, void *source, unsigned int size);
	unsigned int w_tell(void);
	
	void w_vec3(_vector3<float> const & value);

	void w_vec4(_vector4<float> const & value);
	void w_float(float value);
	void w_u64(unsigned __int64 value);
	void w_s64(__int64 value);
	void w_u32(unsigned __int32 value);
	void w_s32(__int32 value);
	void w_u16(unsigned short value);
	void w_s16(short value);
	void w_u8(unsigned char value);
	void w_s8(char value);
	void w_float_q16(float value, float min = 0, float max = 1.f);
	void w_float_q8(float value, float min = 0, float max = 1.f);
	void w_angle16(float value);
	void w_angle8(float value);
	void w_dir(_vector3<float> const & value);
	void w_sdir(_vector3<float> const & value);
	void w_stringZ(char const * value);

	void w_matrix(_matrix<float> & value);

	void w_clientID(void * value);
	void w_chunk_open8(unsigned int & value);
	void w_chunk_close8(unsigned int value);
	void w_chunk_open16(unsigned int & value);
	void w_chunk_close16(unsigned int value);
	// read
	void r(void *dst, unsigned int size);
	void read_start(void);
	unsigned int r_begin(unsigned short	& id);
	void r_seek(unsigned int pos);
	unsigned int r_tell(void);
	void r_vec3(_vector3<float> & value);
	void r_vec4(_vector4<float> & value);
	void r_float(float & value);
	void r_u64(unsigned __int64 & value);
	void r_s64(__int64 & value);
	void r_u32(unsigned __int32 & value);
	void r_s32(__int32 & value);
	void r_u16(unsigned short & value);
	void r_s16(short & value);
	void r_u8(unsigned char & value);
	void r_s8(char & value);
	void r_float_q16(float & value, float min = 0, float max = 1.f);
	void r_float_q8(float & value, float min = 0, float max = 1.f);
	void r_angle16(float & value);
	void r_angle8(float & value);
	void r_dir(_vector3<float> & value);
	void r_sdir(_vector3<float> & value);
	void r_stringZ(char * value);
	void r_matrix(_matrix<float> & value);
	void r_clientID(void * value);
	unsigned int r_elapsed(void);
	void r_advance(unsigned int ofs);
	void skip_stringZ(void);
	int r_eof(void);
	// vars
	unsigned long	unknown1;				// 0x0
	char			packet_buffer[0x4000];	// 0x4
	unsigned long	packet_write_pos;		// 0x4004
	unsigned long	packet_read_pos;		// 0x4008
	unsigned long	unknown2;				// 0x400C
	char			w_allow;				// 0x4010
};