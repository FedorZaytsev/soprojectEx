/*
*	S.T.A.L.K.E.R.- utils for X-Ray
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#pragma once

template<typename TYPE> struct _vector3
{
	union 
	{
		struct 
		{
			TYPE x, y, z;
		};
		TYPE xyz[3];
	};
};

template<typename TYPE> struct _vector4
{
	TYPE x, y, z, w;
};

template<typename TYPE> struct _matrix
{
	union 
	{
		struct 
		{
			TYPE _11, _12, _13;
			TYPE _21, _22, _23;
			TYPE _31, _32, _33;
		};
		struct 
		{
			_vector3<TYPE>	i;
			_vector3<TYPE>	j;
			_vector3<TYPE>	k;
		};
		TYPE m[3][3];
	};
};

template<typename TYPE> struct _box3 // simple copy of matrix
{
	union 
	{
		struct 
		{
			TYPE _11, _12, _13;
			TYPE _21, _22, _23;
			TYPE _31, _32, _33;
		};
		struct 
		{
			_vector3<TYPE>	i;
			_vector3<TYPE>	j;
			_vector3<TYPE>	k;
		};
		TYPE m[3][3];
	};
};

class shared_str
{
public:
	shared_str(void);
	~shared_str(void);
};