/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Z-Engine\ZEnginePC.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"

// Renderer
#include "RendererLib/RendererContext.h"
#include "RendererLib/RenderEffectManager.h"
#include "XMLRenderEffectIO/XMLRenderEffectIO.h"

// input 
#include "InputLib/InputInterface.h"

// camera 
#include "CameraLib/CameraInterface.h"

// sprite
#include "SpriteLib/SpriteInterface.h"
#include "SpriteLib/SpriteManager.h"
#ifdef USING_XML_SPRITE_IO
#include "XMLSpriteIO/XMLSpriteParser.h"
#endif
#include "SpriteLib/2DRenderList.h"

// scene 
#include "SceneLib/SceneInterface.h"


// Implementations
#include "DX9RendererLib/DX9Renderer.h"

// Windows platform, windows supports mouse and keyboard
#include "DInputLib/DMouse.h"
#include "DInputLib/KeyBoard.h"

#include "CoreLib/Clock.h"
#include "CoreLib/PerformanceManager.h"

// This include
#include "Z-Engine/ZEnginePC.h"
using namespace ZGE;

ZEnginePC::ZEnginePC(void)
{
}

ZEnginePC::~ZEnginePC(void)
{
}

		// Runs the game loop.
bool  ZEnginePC::Run( )
{
	// Windows message pump.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// Sync the clock.
	sm_pClock->Process( );
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			sm_pClock->Process( );
			// Update the game.
			if( false ==  sm_pRendererContext->FrameUpdate( ) )
			{
				break;
			}

			// Begin the scene.
			if( false == sm_pRendererInterface->BeginScene( ) )
			{
				break;
			}

			// Render the game.
			if( false == sm_pRendererContext->FrameDraw( ) )
			{
				sm_pRendererInterface->EndScene( );
				break;
			}

			// Present and end the scene.
			if( false == sm_pRendererInterface->EndScene( ) )
			{
				break;
			}
		}
	}
	return false;
}


// Instantiales the renderer based on preprocessor defines.
bool ZEnginePC::InitialiseRendererInterface( )
{
	// For PC we can either use the DirectX or open GL.
	sm_pRendererInterface = new CDX9Renderer( );
	sm_pRendererInterface->CreateRenderContext( sm_pRendererContext );

	//IRenderEffectIO* pRenderEffectIO = NULL;
	//pRenderEffectIO = new CXMLRenderEffectIO( );
	//sm_pRendererInterface->GetRenderEffectManager( )->Initialise( pRenderEffectIO );
	return true;
}

// Initialises input.
bool ZEnginePC::InitialiseInputInterface( )
{
	sm_pInputInterface = new CInputInterface( );

 //Windows platform, windows supports mouse and keyboard
	IMouse* pMouse = new CDMouse( );
	IKeyBoard* pKeyBoard = new CKeyBoard( );
	sm_pInputInterface->Initialise( pKeyBoard, pMouse );
	return false;
}
/*
// Initialises the physics interface.
bool ZEnginePC::InitialisePhysicsInterface( )
{
	return false;
}

// Initialises the GUI system.
bool ZEnginePC::InitialiseGUIInterface( )
{
	return false;
}

*/

// Initialises the scene interface.
bool ZEnginePC::InitialiseSceneInterface( )
{
	sm_pSceneInterface = new CSceneInterface( );
	sm_pSceneInterface->Initialise( );
	return false;
}

// Initialises the camera interface.
bool ZEnginePC::InitialiseCameraInterface( )
{
	sm_pCameraInterface = new CCameraInterface( );
	return true;
}
/*
// Initialises the sprite interface.
bool ZEnginePC::InitialiseSpriteInterface( )
{
	sm_pSpriteInterface = new CSpriteInterface( );
	sm_pSpriteInterface->InitialiseSpriteInterface( );

	ISpriteParser* pSpriteParser = NULL;
#ifdef USING_XML_SPRITE_IO
	pSpriteParser = new CXMLSpriteParser( );
#endif
	
	pSpriteParser->Initialise( sm_pRendererInterface->GetTextureManager( ) );
	sm_pSpriteInterface->GetSpriteManager( )->SetSpriteParser( pSpriteParser );

	C2DRenderList* pSpriteRenderList = new C2DRenderList( );
	sm_pRendererInterface->AddRenderList( pSpriteRenderList );
	return false;
}

*/

// Initialises the clock.
bool ZEnginePC::InitialiseClock( )
{
	sm_pClock = new CClock( );
	sm_pClock->Initialise( );
	return true;
}

// Deinitilaise.

// Deinitilaise the renderer.
bool ZEnginePC::DeinitialiseRendererInterface( )
{
	sm_pRendererInterface->ShutDown( );
	SafeDelete( sm_pRendererInterface );
	return false;
}

// Deinitilaise input.
bool ZEnginePC::DeinitialiseInputInterface( )
{
	SafeDelete( sm_pInputInterface );
	return false;
}

// Deinitilaise the physics interface.
/*
bool ZEnginePC::DeinitialisePhysicsInterface( )
{
	return false;
}
*/
/*
// Deinitilaise the GUI system.
bool ZEnginePC::DeinitialiseGUIInterface( )
{
	return false;
}
*/

// Deinitilaise the scene interface.
bool ZEnginePC::DeinitialiseSceneInterface( )
{
	return false;
}

// Deinitilaise the camera interface.
bool ZEnginePC::DeinitialiseCameraInterface( )
{
	SafeDelete( sm_pCameraInterface );
	return false;
}

/*
// Deinitilaise the sprite interface.
bool ZEnginePC::DeinitialiseSpriteInterface( )
{
	SafeDelete( sm_pSpriteInterface );
	return false;
}

*/
// Deinitialises the clock.
void ZEnginePC::DeinitialiseClock( )
{
	SafeDelete( sm_pClock );
}


