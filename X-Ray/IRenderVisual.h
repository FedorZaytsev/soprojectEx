/*
*	S.T.A.L.K.E.R.- IRenderVisual class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "./dxRender_Visual.h"
#include "./CKinematics.h"
#include "./CKinematicsAnimated.h"

class IRenderVisual
{
public:
	IRenderVisual(void);
	~IRenderVisual(void);

	dxRender_Visual Visual;
	// CKinematics
	CKinematics Kinematics;
	// CKinematicsAnimated
	CKinematicsAnimated KinematicsAnimated;
};