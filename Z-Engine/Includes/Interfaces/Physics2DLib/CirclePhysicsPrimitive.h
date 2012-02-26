/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\CirclePhysicsPrimitive.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _CIRCLEPHYSICSPRIMITIVE_H__Included_627234322
#define _CIRCLEPHYSICSPRIMITIVE_H__Included_627234322

#include "2DPhysicsPrimitive.h" 
namespace ZGE
{
	/**
	 *	A circle physics priitive.
	 */
	class ICirclePhysicsPrimitive : public I2DPhysicsPrimitive
	{
	public:
		ICirclePhysicsPrimitive( )
		{
			m_e2DPhysicsPrimitiveType = _2D_PHYSICS_CIRCLE_PRIMITIVE;
		}
		virtual ~ICirclePhysicsPrimitive( ){ }
	protected:
		

	};
}

#endif //_CIRCLEPHYSICSPRIMITIVE_H__Included_627234322

