/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\ZEngine.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ZENGINE_H__Included_1618877053
#define _ZENGINE_H__Included_1618877053

// http://www.it-c.dk/people/olav/Thesis.pdf

// Note: This class causes the engine to not build unless the exe class is linked to every thing.
// A method around this is to put defines for functionaliy wanted.
// i.e. #define USING_SCENE_INTERFACE
//	    #define USING_CAMERA_INTERFACE etc.

#include "Z-Engine/ZPlatformDefines.h"

namespace ZGE
{
	// prototypes 
	class IRendererContext;
	class IRendererInterface;
	class IPhysicsInterface;
	class IGUIInterface;
	class CSceneInterface;
	class CInputInterface;
	class CCameraInterface;
	class CSpriteInterface;
	class CClock;

	/**
	 * This class represents the engine.
	 * It is repsonsible for the iniialisation and deinitialisation of the engine.
	 */
	class ZEngine
	{
	public:

		// initialises the engine using the renderer context.
		 bool InitialiseZEngine( IRendererContext* _kpRenderContext );

		// Deinitialise the engine.
		 bool DeinitialiseZEngine(  );

		// Returns the engine render context.
		static inline IRendererContext* GetRendererContext( ) { return sm_pRendererContext; }

		// Returns the engines renderer interface implementation.
		static inline IRendererInterface* GetRendererInterface( ) { return sm_pRendererInterface; }

		// Returns the engines physics interface implementation.
		//static inline IPhysicsInterface* GetPhysicsInterface( ) { return sm_pPhysicsInterface; }

		// Returns the engines GUI interface implementation.
		//static inline IGUIInterface* GetGUIInterface( ) { return sm_pGUIInterface; }

		// Returns the engines scene interface.
		static inline CSceneInterface* GetSceneInterface( ) { return sm_pSceneInterface; }

		// Returns the input interface.
		static inline CInputInterface* GetInputInterface( ) { return sm_pInputInterface; }

		// Returns the camera interface.
		static inline CCameraInterface* GetCameraInterface( ){ return sm_pCameraInterface; }

		// Returns the sprite interface
		//static inline CSpriteInterface* GetSpriteInterface( ){ return sm_pSpriteInterface; }

		// Returns the clock.
		static inline CClock* GetClock( ){ return sm_pClock; } 

		// Runs the game loop.
		virtual bool Run( ) = 0;

		// Sets the run time directory.
		static void SetRuntimeDirectory( const char* _kpcRuntimeDirectory );

		// Gets the runtime directory.
		static const char* GetRuntimeDirectory( );
	protected:

		// Instantiales the renderer based on preprocessor defines.
		virtual bool InitialiseRendererInterface( ) = 0;

		// Initialises input.
		virtual bool InitialiseInputInterface( ) = 0;

		// Initialises the physics interface.
		//virtual bool InitialisePhysicsInterface( ) = 0;

		// Initialises the GUI system.
		//virtual bool InitialiseGUIInterface( ) = 0;

		// Initialises the scene interface.
		virtual bool InitialiseSceneInterface( ) = 0;

		// Initialises the camera interface.
		virtual bool InitialiseCameraInterface( ) = 0;

		// Initialises the sprite interface.
		//virtual bool InitialiseSpriteInterface( ) = 0;

		// Initialises the clock.
		virtual bool InitialiseClock( ) = 0;

	// Deinitilaise.

				// Deinitilaise the renderer.
		virtual bool DeinitialiseRendererInterface( ) = 0;

		// Deinitilaise input.
		virtual bool DeinitialiseInputInterface( ) = 0;

		// Deinitilaise the physics interface.
		//virtual bool DeinitialisePhysicsInterface( ) = 0;

		// Deinitilaise the GUI system.
		//virtual bool DeinitialiseGUIInterface( ) = 0;

		// Deinitilaise the scene interface.
		virtual bool DeinitialiseSceneInterface( ) = 0;

		// Deinitilaise the camera interface.
		virtual bool DeinitialiseCameraInterface( ) = 0;

		// Deinitilaise the sprite interface.
		//virtual bool DeinitialiseSpriteInterface( ) = 0;

		// Deinitialises the clock.
		virtual void DeinitialiseClock( ) = 0;

		// Initilaises the performance manager.
		void InitialisePerformanceManager( );

	protected:

		static IRendererContext*    sm_pRendererContext;	//!< The renderer context.
		static IRendererInterface*  sm_pRendererInterface;	//!< The renderer implementation.
	//	static IPhysicsInterface*	sm_pPhysicsInterface;	//!< The physics implementation.
		//static IGUIInterface*		sm_pGUIInterface;		//!< The Gui implementation.
		static CSceneInterface*	    sm_pSceneInterface;		//!< The scene interface.
		static CInputInterface*     sm_pInputInterface;		//!< The input interface.
		static CCameraInterface*	sm_pCameraInterface;	//!< The camera interface.
		//static CSpriteInterface*	sm_pSpriteInterface;	//!< The sprite interface"
		static CClock*				sm_pClock;				//!< The engines clock.
#define Z_MAX_DIRECTORY_PATH 1024
		static char					sm_pcRuntimeDirectory[Z_MAX_DIRECTORY_PATH];
	};
}// end name space

#endif //_ZENGINE_H__Included_1618877053

