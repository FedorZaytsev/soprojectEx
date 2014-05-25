/*
*	S.T.A.L.K.E.R.- CLocatorAPI class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "IReader.h"

class __declspec(dllimport) CLocatorAPI
{
public:
	CLocatorAPI();
	~CLocatorAPI();

	struct file
	{
		int unk;
	};

	//int LoadArchive(archive &, char const *Src);
	void ProcessArchive(char const *);
	file const * exist(char (&)[520],char const* , char const* , char const* );
	IReader* r_open(char const *);
};