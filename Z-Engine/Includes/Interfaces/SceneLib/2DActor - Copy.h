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

namespace ZGE
{
	/**
	 * Represents an actor in screen space
	 */
	class C2DActor
	{
	public:
		C2DActor(void);
		~C2DActor(void);

		// Returns the actors screen space position.
		inline const CFVec3& GetPosition( ) { return m_v3Position; }

		// Returns the actors transformation from it's parent.
		inline const CFVec3 GetTransformVector( ) { return m_v3TRansform; }

		// Sets the actors trasnfrom atoin from it's parent.
		inline void SetTransform( const CFVec3& _krvTransform ) { m_v3Transform = _krvTransform; }

	protected:
		CFVec3 m_v3Position;	//!< The actors position in screen space.
		CFvec3 m_v3Transform;	//!< The actors tranmsform from its parent.
	};
}// end namespace 

#endif //_C2DACTOR_H__Included_1958185341

