/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Z-Engine\ZEnginePC.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright � 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ZENGINEPC_H__Included_384283611
#define _ZENGINEPC_H__Included_384283611

#include "Z-Engine/ZEngine.h"
namespace ZGE
{
	/**
	 *	ZEngine set up for PC.
	 */
	class ZEnginePC : public ZEngine
	{
	public:
		ZEnginePC(void);
		~ZEnginePC(void);

				// Runs the game loop.
		virtual bool Run( );

protected:

			// Instantiales the renderer based on preprocessor defines.
		virtual bool InitialiseRendererInterface( );

		// Initialises input.
		virtual bool InitialiseInputInterface( );

		// Initialises the physics interface.
		//virtual bool InitialisePhysicsInterface( );

		// Initialises the GUI system.
		//virtual bool InitialiseGUIInterface( );

		// Initialises the scene interface.
		virtual bool InitialiseSceneInterface( );

		// Initialises the camera interface.
		virtual bool InitialiseCameraInterface( );

		// Initialises the sprite interface.
		//virtual bool InitialiseSpriteInterface( );
		
		// Initialises the clock.
		virtual bool InitialiseClock( );
	// Deinitilaise.

				// Deinitilaise the renderer.
		virtual bool DeinitialiseRendererInterface( );

		// Deinitilaise input.
		virtual bool DeinitialiseInputInterface( );

		// Deinitilaise the physics interface.
		//virtual bool DeinitialisePhysicsInterface( );

		// Deinitilaise the GUI system.
		//virtual bool DeinitialiseGUIInterface( );

		// Deinitilaise the scene interface.
		virtual bool DeinitialiseSceneInterface( );

		// Deinitilaise the camera interface.
		virtual bool DeinitialiseCameraInterface( );

		// Deinitilaise the sprite interface.
		//virtual bool DeinitialiseSpriteInterface( );

			// Deinitialises the clock.
		virtual void DeinitialiseClock( );
	};
}

#endif //_ZENGINEPC_H__Included_384283611

