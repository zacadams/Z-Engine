/**
 *	@file Blarg\blarg\C3DActor.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _C3DACTOR_H__Included_958512764
#define _C3DACTOR_H__Included_958512764

#include "Actor.h"

namespace ZGE
{
	/**
	 * Represents an actor in 3D space
	 */
	class C3DActor : public CActor
	{
	public:
		C3DActor(void);
		~C3DActor(void);

		// Returns the actors tranformation from its parent.
		inline CFMat4x4& GetTransformationMatrix( ) { return m_mTransform; }

		// Sets the actors transformation from its parent.
		inline void SetTransformationMatrix( const CFMat4x4& _krmTransform ) { m_mTransform = _krmTransform; }



	protected:
		CFMat4x4 m_mWorldMatrix;		//!< The actors world matrix.
		CFMat4x4 m_mTransform;		//!< Transformation from parent.
		CFMat4x4 m_ScaleMatrix;
		CFMat4x4 m_mOrientationMatrix;
		CFVec3	 m_vWorldDirection;	//!< The actors world space direction.
		CFVec3	 m_vLocalDirection;	//!< The actors local space direction.This can be considered as the local transforms rotation.
	};
}// end namespace 

#endif //_C3DACTOR_H__Included_958512764

