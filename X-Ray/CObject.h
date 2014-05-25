/*
*	S.T.A.L.K.E.R.- CObject class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#pragma once

#include "DLL_Pure.h"
#include "ICollidable.h"
#include "IRenderable.h"
#include "ISheduled.h"
#include "ISpatial.h"
#include "ICollisionForm.h"
#include "IRender_ObjectSpecific.h"
#include "IRender_Sector.h"
#include "IRenderVisual.h"
#include "CSE_Abstract.h"
#include "NET_Packet.h"
#include "utils.h"

class __declspec(dllimport) CObject:
	DLL_Pure,
	ICollidable,
	IRenderable,
	ISheduled,
	ISpatial
{
public:
	struct SavedPosition { float X,Y,Z; };

	CObject(void);
	~CObject(void);

	int AlwaysTheCrow(void);
	bool AmICrow(void) const;

	virtual _box3<float> BoundingBox(void) const;
	
	ICollisionForm * CFORM(void);
	void Center(_vector3<float> &);
	void ForceTransform(_matrix<float> const &);
	int GetTmpPreDestroy(void);
	CObject * H_Parent(void);
	CObject * H_Root(void);
	CObject * H_SetParent(CObject *,bool);
	void IAmNotACrowAnyMore(void);
	unsigned short ID(void) const;
	void Load(char const *);
	int Local(void);
	void MakeMeCrow(void);
	void OnChangeVisual(void);
	void OnHUDDraw(void *);
	void OnH_A_Chield(void);
	void OnH_A_Independent(void);
	void OnH_B_Chield(void);
	void OnH_B_Independent(bool);
	void On_LostEntity(void);
	void On_SetEntity(void);

	_vector3<float> const & Direction(void) const;
	_vector3<float> const & Position(void) const;

	IRender_ObjectSpecific * ROS(void);
	virtual float Radius(void);
	int Ready(void);
	int Remote(void);
	IRender_Sector * Sector(void);
	void SetTmpPreDestroy(int);
	void UpdateCL(void);

	IRenderVisual * Visual(void) const;
	
	_matrix<float> const & XFORM(void) const;

	shared_str cName(void);
	shared_str cNameSect(void);
	void cNameSect_set(shared_str);

	char const * cNameSect_str(void) const;

	shared_str cNameVisual(void);
	void cNameVisual_set(shared_str);
	void cName_set(shared_str);
	CObject * dcast_CObject(void);
	IRenderable * dcast_Renderable(void);
	int getDestroy(void) const;
	int getEnabled(void) const;
	int getLocal(void) const;
	int getReady(void) const;
	int getSVU(void) const;
	int getVisible(void) const;
	_vector3<float> get_last_local_point_on_mesh(_vector3<float> const &,unsigned short);
	_vector3<float> get_new_local_point_on_mesh(unsigned short &);
	void net_Destroy(void);
	
	virtual void net_Export(NET_Packet &);
	virtual void net_Import(NET_Packet &);

	void net_ImportInput(NET_Packet &);
	void net_MigrateActive(NET_Packet &);
	void net_MigrateInactive(NET_Packet &);
	void net_Relcase(CObject *);
	int net_Relevant(void);
	int net_Spawn(CSE_Abstract *);
	int physics_collision(void);
	int physics_shell(void);
	void processing_activate(void);
	void processing_deactivate(void);
	bool processing_enabled(void);
	CObject::SavedPosition ps_Element(unsigned int);
	unsigned int ps_Size(void);
	bool register_schedule(void);
	void renderable_Render(void);
	int renderable_ShadowGenerate(void);
	int renderable_ShadowReceive(void);
	void setDestroy(int);
	void setEnabled(int);
	void setID(unsigned short);
	void setLocal(int);
	void setReady(int);
	void setSVU(int);
	void setVisible(int);
	shared_str shedule_Name(void);
	virtual bool shedule_Needed(void);
	virtual float shedule_Scale(void);
	void shedule_Update(unsigned int);
	void spatial_move(void);
	void spatial_register(void);
	void spatial_unregister(void);
	int spatial_update(float,float);
};