#include "CoreLib/Core.h"
//Renderer
#include "RendererLib/RendererContext.h"
#include "OpenGLES2Renderer/OpenGLES2Renderer.h"
#include "Z-EngineiOS/ZEngineiOS.h"
using namespace ZGE;
ZEngineiOS::ZEngineiOS(void)
{
}

ZEngineiOS::~ZEngineiOS(void)
{
}

		// Runs the game loop.
bool  ZEngineiOS::Run( )
{
#ifdef WIN32
	// Windows message pump.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// Sync the clock.
	//sm_pClock->Process( );
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			//sm_pClock->Process( );
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
#endif
	return false;
	
}


// Instantiales the renderer based on preprocessor defines.
bool ZEngineiOS::InitialiseRendererInterface( )
{
	// For PC we can either use the DirectX or open GL.
	sm_pRendererInterface = new COpenGLES2Renderer( );
	sm_pRendererInterface->CreateRenderContext( sm_pRendererContext );

	/*
	IRenderEffectIO* pRenderEffectIO = NULL;
	pRenderEffectIO = new CXMLRenderEffectIO( );
	sm_pRendererInterface->GetRenderEffectManager( )->Initialise( pRenderEffectIO );
	*/
	return true;
}

// Initialises input.
bool ZEngineiOS::InitialiseInputInterface( )
{
	/*
	sm_pInputInterface = new CInputInterface( );

 //Windows platform, windows supports mouse and keyboard
	IMouse* pMouse = new CDMouse( );
	IKeyBoard* pKeyBoard = new CKeyBoard( );
	sm_pInputInterface->Initialise( pKeyBoard, pMouse );
	*/
	return false;
}

// Initialises the physics interface.
bool ZEngineiOS::InitialisePhysicsInterface( )
{
	return false;
}

// Initialises the GUI system.
bool ZEngineiOS::InitialiseGUIInterface( )
{
	return false;
}

// Initialises the scene interface.
bool ZEngineiOS::InitialiseSceneInterface( )
{
	/*
	sm_pSceneInterface = new CSceneInterface( );
	sm_pSceneInterface->Initialise( );
	*/
	return false;
	
}

// Initialises the camera interface.
bool ZEngineiOS::InitialiseCameraInterface( )
{
	/*
	sm_pCameraInterface = new CCameraInterface( );
	*/
	return true;
	
}

// Initialises the sprite interface.
bool ZEngineiOS::InitialiseSpriteInterface( )
{
	/*
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
	*/
	return false;
	
}

// Initialises the clock.
bool ZEngineiOS::InitialiseClock( )
{
	/*
	sm_pClock = new CClock( );
	sm_pClock->Initialise( );
	*/
	return true;

}

// Deinitilaise.

// Deinitilaise the renderer.
bool ZEngineiOS::DeinitialiseRendererInterface( )
{
	sm_pRendererInterface->ShutDown( );
	SafeDelete( sm_pRendererInterface );
	return false;
}

// Deinitilaise input.
bool ZEngineiOS::DeinitialiseInputInterface( )
{
	
	SafeDelete( sm_pInputInterface );
	return false;
}

// Deinitilaise the physics interface.

bool ZEngineiOS::DeinitialisePhysicsInterface( )
{
	return false;
}

// Deinitilaise the GUI system.
bool ZEngineiOS::DeinitialiseGUIInterface( )
{
	return false;
}

// Deinitilaise the scene interface.
bool ZEngineiOS::DeinitialiseSceneInterface( )
{
	return false;
}

// Deinitilaise the camera interface.
bool ZEngineiOS::DeinitialiseCameraInterface( )
{
	SafeDelete( sm_pCameraInterface );
	return false;
}

// Deinitilaise the sprite interface.
bool ZEngineiOS::DeinitialiseSpriteInterface( )
{
	SafeDelete( sm_pSpriteInterface );
	return false;
}
// Deinitialises the clock.
void ZEngineiOS::DeinitialiseClock( )
{
	SafeDelete( sm_pClock );
}


