/**
 *	@file Blarg\blarg\C2DActor.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _C2DACTOR_H__Included_1958185341
#define _C2DACTOR_H__Included_1958185341


#ifdef USING_SCENE_INTERFACE

#include "SceneLib/Actor.h"
#include "MathLib/FVec3.h"
#include "MathLib/FVec2.h"
#include "MathLib/FMat4x4.h"

namespace ZGE
{
	class CSprite;
	/**
	 * Represents an actor in screen space
	 */
	_ALIGNED_PREFIX( 16 )
	class C2DActor : public CActor
	{
	public:
		C2DActor(void);
		~C2DActor(void);

		//@return The 2d actors orientation.
		inline float32 GetLocalOrientation( ) const { return m_fLocalOrientation; }

		// Returns the actors world orientation.
		inline float32 GetWorldOrientation( ) const { return m_fWorldOrientation; }

		// Sets the actors local orientation.
		inline void SetLocalOrientation( const float32 _kfOrientation ){ m_fLocalOrientation =  _kfOrientation; }

		// Empty process function, to be overidden by derived classes.
		bool Update( const float32 _kfDeltaTick );

		// Empty draw function, to be overidden by derived classes.
		bool Draw(  );

		// This is a pre update.
		virtual bool PreUpdate( const float32 _kfDeltaTick );

	protected:
		float32 m_fWorldOrientation;	//!< The 2d actors rotation in world space.  
		float32 m_fLocalOrientation;	//!< The 2d actors rotation is local space.
	};
}// end namespace 
#endif

#endif //_C2DACTOR_H__Included_1958185341

