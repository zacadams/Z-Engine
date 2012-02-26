/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\2DPhysicsPrimitive.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _2DPHYSICSPRIMITIVE_H__Included_2133872168
#define _2DPHYSICSPRIMITIVE_H__Included_2133872168

#include "PhysicsPrimitive.h"

namespace ZGE
{

	/**
	 *	2D physics primtive types.
	 */
	enum E2DPhysicsPrimtive
	{
		_2D_PHYSICS_BOX_PRIMITIVE = 0,			//!< Box physics primitive run time type.
		_2D_PHYSICS_CIRCLE_PRIMITIVE,			//!< Circle physics primitive run time type.
		_2D_PHYSICS_LINE_PRIMITIVE ,				//!< Line physics primitive run time type.
		_2D_PHYSICS_COMPLEX_POLYGON_PRIMITIVE,	//!< Complex polygon run time type.
	};


	/**
	 *	This is the base for a 2D physiscs primitive.
	 */
	class I2DPhysicsPrimitive : public IPhysicsPrimitive
	{
	public:
		virtual ~I2DPhysicsPrimitive( ){ }

		/**
		 * Checks for an intersection between two 2D primitives.
		 */
		virtual inline bool Intersects( IPhysicsPrimitive* _pPrimitive, CIntersectionInfo& _rIntersectionInfo  )
		{
			switch( _pPrimitive->GetPrimitiveId( ) )
			{
			case _2D_PHYSICS_BOX_PRIMITIVE:
				{	
					BoxIntersection( _pPrimitive, _rIntersectionInfo );
				}
				break;
			case _2D_PHYSICS_CIRCLE_PRIMITIVE:
				{
					CircleIntersection( _pPrimitive, _rIntersectionInfo );
				}
				break;
			case _2D_PHYSICS_LINE_PRIMITIVE:
				{
					LineIntersection( _pPrimitive, _rIntersectionInfo );
				}
				break;
			case _2D_PHYSICS_COMPLEX_POLYGON_PRIMITIVE:
				{
					ComplexPolygonIntersection( _pPrimitive, _rIntersectionInfo );
				}
				break;
			default:return false;
			}
			return false;
		}

		/** 
		 *	Performs a box intersection test..
		 */
		virtual bool BoxIntersection( IPhysicsPrimitive* _pPrimitive, CIntersectionInfo& _rIntersectionInfo ) = 0;
		
		/** 
		*	Performs a circle intersection test.
		*/
		virtual bool CircleIntersection( IPhysicsPrimitive* _pPrimitive, CIntersectionInfo& _rIntersectionInfo ) = 0;

		/**
		 *	Performs a line intersection test.
		 */
		virtual bool LineIntersection( IPhysicsPrimitive* _pPrimitive, CIntersectionInfo& _rIntersectionInfo ) = 0;

		/**
		 *	Performs a complex polygon intersection test.
		 */
		virtual bool ComplexPolygonIntersection( IPhysicsPrimitive* _pPrimitive, CIntersectionInfo& _rIntersectionInfo ) = 0;

		/**
		 *	Overrloadded to return a 2D primitive type id.
		 */
		virtual inline  uint32 GetPrimitiveId( )
		{
			return m_e2DPhysicsPrimitiveType;
		}

	protected:
		E2DPhysicsPrimtive m_e2DPhysicsPrimitiveType;
	};
}

#endif //_2DPHYSICSPRIMITIVE_H__Included_2133872168

