/*
*	S.T.A.L.K.E.R.- CEvent class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "IEventReceiver.h"

class __declspec(dllimport) CEvent
{
public:
	CEvent();
	~CEvent();

	void Attach(IEventReceiver *);
	void Detach(IEventReceiver *);
	int Equal(CEvent &);
	char const * GetFull(void);
	unsigned int RefCount(void);
	void Signal(unsigned __int64,unsigned __int64);
};