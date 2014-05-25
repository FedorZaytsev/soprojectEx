/*
*	S.T.A.L.K.E.R.- IRenderable class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "IRender_ObjectSpecific.h"

class __declspec(dllimport) IRenderable
{
public:
	IRenderable(void);
	~IRenderable(void);

	IRender_ObjectSpecific * renderable_ROS(void);
	int renderable_ShadowGenerate(void);
	int renderable_ShadowReceive(void);
};