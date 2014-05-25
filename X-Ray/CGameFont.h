/*
*	S.T.A.L.K.E.R.- CGameFont class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#pragma once

#include "utils.h"

class __declspec(dllimport) CGameFont
{
public:
	CGameFont(char const *,char const *,unsigned int);
	~CGameFont();

	enum EAligment
	{
		ALIGMENT_LEFT,
		ALIGMENT_CENTER,
		ALIGMENT_RIGHT
	};

	void Clear(void);
	float CurrentHeight_(void);
	_vector3<float> GetCharTC(unsigned short);
	unsigned short GetCutLengthPos(float,char const *);
	float GetHeight(void);
	void Initialize(char const *,char const *);
	int IsMultibyte(void);
	int MasterOut(int,int,int,int,float,float,float,char const *,char *);
	void OnRender(void);
	void Out(float,float,char const *,...);
	int OutI(float,float,char const *,...);
	void OutNext(char const *,...);
	void OutSet(float,float);
	int OutSetI(float,float);
	void OutSkip(float);
	void SetAligment(CGameFont::EAligment);
	void SetColor(unsigned int);
	void SetHeight(float);
	int SetHeightI(float);
	void SetHudAffect(bool);
	int SetInterval(float,float);
	float SizeOf_(char const *);
	unsigned short SplitByWidth(unsigned short *,unsigned short,float,char const *);
	int smart_strlen(char const *);
};