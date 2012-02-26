/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\BoxPhysicsPrimitive.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _BOXPHYSICSPRIMITIVE_H__Included_933405414
#define _BOXPHYSICSPRIMITIVE_H__Included_933405414

#include "2DPhysicsPrimitive.h"

namespace ZGE
{
	/**
	 *	A box physics primitive. 
	 */
	class IBoxPhysicsPrimitive : public I2DPhysicsPrimitive
	{
	public:
		IBoxPhysicsPrimitive(void)
		{ 
			m_e2DPhysicsPrimitiveType= _2D_PHYSICS_BOX_PRIMITIVE ;
		}
		virtual ~IBoxPhysicsPrimitive( ){ }

	protected:
	};
}

#endif //_BOXPHYSICSPRIMITIVE_H__Included_933405414

