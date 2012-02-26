/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\PhysicsPrimitive.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _PHYSICSPRIMITIVE_H__Included_1550764229
#define _PHYSICSPRIMITIVE_H__Included_1550764229

#include "MathLib/FMat4x4.h"
namespace ZGE
{
	class CCollisionInfo;
	class CIntersectionInfo;
	/** 
	 *	The base for all physics primitives.
	 */
	class IPhysicsPrimitive
	{
	public:
		/**
		 *	Call back for collisions.	
		 */
		virtual void OnCollision( CCollisionInfo& _rCollitionInfo ) = 0;

		/**
		 *	Sets the primitives user data.
		 */
		inline void SetUserData( void* _pUserData ){ m_pUserData = _pUserData; } 

		/**
		 * Checks for an intersection between two primitives.
		 */
		virtual bool Intersects( IPhysicsPrimitive* _pPrimitive, CIntersectionInfo& _rIntersectionInfo  ) = 0;

		/**
		 *	Overrloadded to return a 2D primitive type id.
		 */
		virtual inline  uint32 GetPrimitiveId( ) = 0;

		/**
		 *	Sets the physics primitives transform.
		 */
		inline void SetTransform( const CFMat4x4& _krmTransform ) { m_mTransform = _krmTransform; }

		/**
		 *	returns the physics primitives transform.
		 */
		inline const CFMat4x4& GetTransform( ) const { return m_mTransform; }
	protected:
	protected:
		void*	 m_pUserData;	 //!< The physics primitives user data.
		CFMat4x4 m_mTransform;
	};
}



#endif //_PHYSICSPRIMITIVE_H__Included_1550764229

