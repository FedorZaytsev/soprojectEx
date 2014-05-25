/*
*	S.T.A.L.K.E.R.- ISheduled class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "utils.h"

class __declspec(dllimport) ISheduled
{
public:
	ISheduled(void);
	~ISheduled(void);

	shared_str shedule_Name(void);
	void shedule_Update(unsigned int);
	void shedule_register(void);
	void shedule_unregister(void);
};