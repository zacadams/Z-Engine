/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\C2DPhysicsWorldDesc.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _C2DPHYSICSWORLDDESC_H__Included_88279465
#define _C2DPHYSICSWORLDDESC_H__Included_88279465

#include "MathLib/FVec2.h"
namespace ZGE
{
	/**
	 *	The 2D physics world description.
	 */
	class C2DPhysicsWorldDesc
	{
	public:
		C2DPhysicsWorldDesc( const CFVec2& _krGravity );
		~C2DPhysicsWorldDesc(void);
		CFVec2 m_vGravity;	//!< The gravity direction.
	};
}

#endif //_C2DPHYSICSWORLDDESC_H__Included_88279465

