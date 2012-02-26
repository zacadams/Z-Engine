/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\ZEngine.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"
#include "Z-Engine/ZPlatformDefines.h"

// Renderer context
#include "RendererLib/RendererContext.h"

// Renderer 
#include "RendererLib/RendererInterface.h"


#include "SceneLib/SceneInterface.h"
#include "CameraLib/CameraInterface.h"
//
//// Sprite
#include "SpriteLib/SpriteInterface.h"
#include "SpriteLib/ISpriteParser.h"
#include "XMLSpriteIO/XMLSpriteParser.h"

// Performance
#include "CoreLib/PerformanceManager.h"

#include "Z-Engine/ZEngine.h"

using namespace ZGE;

IRendererContext*   ZEngine::sm_pRendererContext    = NULL;	// The renderer context.
IRendererInterface* ZEngine::sm_pRendererInterface  = NULL;	// The renderer implementation.
//IPhysicsInterface*	ZEngine::sm_pPhysicsInterface   = NULL;	// The physics implementation.
//IGUIInterface*		ZEngine::sm_pGUIInterface       = NULL;	// The Gui implementation.
CSceneInterface*	ZEngine::sm_pSceneInterface     = NULL;	// The scene interface.
CInputInterface*    ZEngine::sm_pInputInterface     = NULL;	// The input interface.
CCameraInterface*   ZEngine::sm_pCameraInterface    = NULL;
//CSpriteInterface*	ZEngine::sm_pSpriteInterface    = NULL;
CClock*				ZEngine::sm_pClock				= NULL;

char ZEngine::sm_pcRuntimeDirectory[Z_MAX_DIRECTORY_PATH] = { '\0' };

/**
 *initialises the engine using the renderer context.
 * @param  _kpRendererContext To be used to initialise the engine.
 * @return Success.
 */
 bool ZEngine::InitialiseZEngine( IRendererContext* _kpRenderContext )
 {
	// Store the renderer context.
	sm_pRendererContext = _kpRenderContext;
	
	// Note: initialise the renderer interface first.
	InitialiseRendererInterface( );
	//InitialiseSpriteInterface( );
	InitialiseSceneInterface( );
	InitialiseInputInterface( );
	InitialiseCameraInterface( );
	//InitialisePhysicsInterface( );
	//InitialiseGUIInterface( );
	InitialiseClock( );

#ifdef Z_ENABLE_PERFORMANCE_TEST
	InitialisePerformanceManager( );
#endif

	 return true;
 }

/**
 * Deinitialise the engine.
 * @return Success.
 */
 bool ZEngine::DeinitialiseZEngine(  )
{
	sm_pRendererContext->Deinitialise( );
	DeinitialiseCameraInterface( );
	DeinitialiseSceneInterface( );
	DeinitialiseCameraInterface( );
	//DeinitialiseGUIInterface( );
	DeinitialiseInputInterface( );
	//DeinitialisePhysicsInterface( );
	//DeinitialiseSpriteInterface( );
	DeinitialiseRendererInterface( );
	DeinitialiseClock( );

#ifdef Z_ENABLE_PERFORMANCE_TEST
	CPerformanceManager::DestroyInstance( );
#endif

//	// Deinitialise the render context.
//	assert_msg( sm_pRendererContext->Deinitialise( ), "Failed to deinitialise the render context!" );
//	
//#ifdef USING_SCENE_INTERFACE
//	// Deinitialise the scene interface.
//	sm_pSceneInterface->DeinitialiseScene( );
//	SafeDelete( sm_pSceneInterface );
//#endif
//#ifdef USING_SPRITE_INTERFACE
//	sm_pSpriteInterface->DeinitilaiseSpriteInterface( );
//	SafeDelete( sm_pSpriteInterface );
//#endif
//	// Deinitialise the renderer interface .
//	assert_msg( sm_pRendererInterface->ShutDown( ), "Failed to shut down the renderer!" );
//	SafeDelete( sm_pRendererInterface );
//
//#ifdef USING_INPUT_INTERFACE
//	SafeDelete( sm_pInputInterface );
//#endif

	return false;
}


//// Runs the game loop.
// bool ZEngine::Run( )
//{
//#ifdef Z_PLATFORM_WIN
//	// windows update loop.
//	MSG msg;
//	ZeroMemory(&msg, sizeof(MSG));
//
//	while (msg.message != WM_QUIT)
//	{
//		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			if( false ==  sm_pRendererContext->FrameUpdate( ) )
//			{
//				break;
//			}
//		}
//	}
//
//	return false;
//	//return (static_cast<int>(msg.wParam));
//
//#endif
//
//}

// Sets the run time directory.
 void ZEngine::SetRuntimeDirectory( const char* _kpcRuntimeDirectory )
{
	sprintf_s( sm_pcRuntimeDirectory, "%s", _kpcRuntimeDirectory ); 
}

// Gets the runtime directory.
 const char* ZEngine::GetRuntimeDirectory( )
 {
	 return sm_pcRuntimeDirectory;
 }



///**
// * Instantiales the renderer based on preprocessor defines.
// * @return Success.
// */
// bool ZEngine::InitialiseRendererInterface( )
//{
//#ifdef Z_PLATFORM_WIN
//
//	// This is a windows application.
//	// Create a DirectX renderer.
//	#include "Dx9RendererLib/DX9Renderer.h"	
//   
//	// Create a directX9 renderer.
//	sm_pRendererInterface = new CDX9Renderer( );
//
//	// Initilaise the renderer.
//	sm_pRendererInterface->Initialise( );
//	return ( sm_pRendererInterface->CreateRenderContext( sm_pRendererContext ) );
//#endif
//
//	return false;
//}

/**
 * Initialises input.
 * @return Success.
 */
//bool ZEngine::InitialiseInputInterface( )
//{
//	if( NULL == sm_pInputInterface )
//	{
//		sm_pInputInterface = new CInputInterface( );
//		return sm_pInputInterface->Initialise( );
//	}
//	return false;
//}
//#endif

/**
 * Initialises the physics interface.
 * @return Success.
 */
//bool ZEngine::InitialisePhysicsInterface( )
//{
//	return false;
//}
//
///**
// * Initialises the GUI system.
// * @return Success.
// */
//bool ZEngine::InitialiseGUIInterface( )
//{
//	return false;
//}
//
///**
// * Initialises the scene interface.
// * @return Success.
// */
//bool ZEngine::InitialiseSceneInterface( )
//{
//	if( NULL == sm_pSceneInterface )
//	{
//		sm_pSceneInterface = new CSceneInterface( );
//		return true;
//	}
//	return false;
//}
//// Initialises the camera interface.
//bool ZEngine::InitialiseCameraInterface( )
//{
//	if( NULL == sm_pCameraInterface )
//	{
//		sm_pCameraInterface = new CCameraInterface( );
//		return true;
//	}
//	return false;
//}
//// Initialises the sprite interface.
//bool ZEngine::InitialiseSpriteInterface( )
//{
//	if( NULL == sm_pSpriteInterface )
//	{
//		sm_pSpriteInterface = new CSpriteInterface( );
//		sm_pSpriteInterface->InitialiseSpriteInterface( );
//
//#ifdef USING_XML_SPRITE_IO
//		// Set up the sprite and animated sprite IO.
//		ISpriteParser* pSpriteParser = new CXMLSpriteParser( );
//		pSpriteParser->Initialise( ZEngine::GetRendererInterface( )->GetTextureManager( ) );
//		sm_pSpriteInterface->SetSpriteParser( pSpriteParser );
//#endif
//		return true;
//	}
//	return false;
//}

void ZEngine::InitialisePerformanceManager( )
{
	CPerformanceManager::GetInstance( );
}

