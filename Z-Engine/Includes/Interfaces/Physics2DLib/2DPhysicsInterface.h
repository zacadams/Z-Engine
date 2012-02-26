/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\2DPhysicsInterface.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _2DPHYSICSINTERFACE_H__Included_8717112
#define _2DPHYSICSINTERFACE_H__Included_8717112

namespace ZGE
{
	class C2DPhysicsBodyDesc;
	class C2DPhysicsWorldDesc;
	class IPhysicsPrimitive;
	/**
	 *	The 2D physics system interface.
	 */
	class I2DPhysicsInterface
	{
	public:
		I2DPhysicsInterface( ) { }
		virtual ~I2DPhysicsInterface( ) { }

		/**
		 *	Initilaises the 2D physics interface.
		 */
		virtual bool Initialise( C2DPhysicsWorldDesc& _rPhysicsWorldDesc ) = 0;

		/**
		 *	Creates an instance of a 2D physics primitive.
		 */
		virtual bool Create2DPhysicsPrimtitive(  const uint32 _kuPrimitiveId, IPhysicsPrimitive*& _p2DPhysicsPrimitive, C2DPhysicsBodyDesc& _rPhysicsBodyDesc ) = 0;
	protected:
	};
}

#endif //_2DPHYSICSINTERFACE_H__Included_8717112

