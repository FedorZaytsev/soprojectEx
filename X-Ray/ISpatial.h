/*
*	S.T.A.L.K.E.R.- ISpatial class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "utils.h"

class __declspec(dllimport) ISpatial
{
public:
	ISpatial(void);
	~ISpatial(void);

	void * dcast_CObject(void);
	void * dcast_FeelSound(void);
	void * dcast_Light(void);
	void * dcast_Renderable(void);
	int spatial_inside(void);
	void spatial_move(void);
	void spatial_register(void);
	_vector3<float> spatial_sector_point(void);
	void spatial_unregister(void);
	void spatial_updatesector(void);
	void spatial_updatesector_internal(void);
};