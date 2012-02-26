/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\CollisionInfo.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _COLLISIONINFO_H__Included_40335126
#define _COLLISIONINFO_H__Included_40335126

namespace ZGE
{	
	class IPhysicsPrimitive;
	/**
	 *	This class contains theinformation for a collision that occured.
	 */
	class CCollisionInfo
	{
	public:
		CCollisionInfo(void);
		~CCollisionInfo(void);
	protected:
		IPhysicsPrimitive* m_ppIntersectingPrimitives[2];	//!< The intersecting primitives.
		float32			   m_fForce;						//!< The force of the collision.
	};
}

#endif //_COLLISIONINFO_H__Included_40335126

