/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Renderer.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/


// Engine includes 
#include "CoreLib/Core.h"
#include "RendererLib/RendererContext.h"
//#include "RendererLib/PrimitiveTypes.h"
//#include "RendererLib/RendererTypes.h"

#include "RendererLib/RenderEffectManager.h"
// Vertex declarations 

#include "RendererLib/VertexDeclarationManager.h"
#include "DX9RendererLib/DX9VertexDeclarationManager.h"
#include "DX9RendererLib/DX9VertexBufferManager.h"

// Texture 

#include "RendererLib/TextureManager.h"
#include "DX9RendererLib/DX9TextureManager.h"

// Lights 

#include "DX9RendererLib/DX9LightManager.h"

// Materials

#include "DX9RendererLib/DX9MaterialManager.h"

// Maths

#include "MathLib/FMat4x4.h"

// Effects 

#include "DX9RendererLib/DX9EffectManager.h"

// Library includes 

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <windowsx.h>

#include<string>

#include "RendererLib/Vertex.h"

#include "DX9RendererLib/DX9Renderer.h"

using namespace ZGE;

IDirect3DDevice9* CDX9Renderer::sm_pDevice = NULL;

CDX9Renderer::CDX9Renderer(void)
: m_pD3D		( NULL )
, m_pDefaultVertexDecl ( NULL )
, m_pTextureMngr( NULL )
, m_pMaterialMngr( NULL )
, m_pEffectMngr( NULL )
, m_pVertexBufferMngr( NULL )
{
}
//
CDX9Renderer::~CDX9Renderer(void)
{

	ShutDown( );

}
/*
*	Added to enfore the deletion and clean up of the rendering system 
*/
bool CDX9Renderer::ShutDown( )
{
	// Release DirectX and delete any allocated memory and resources
	
	SafeDelete( m_pDeclManager );
	SafeDelete( m_pTextureMngr );
	SafeDelete( m_pLightMngr );
	SafeDelete( m_pMaterialMngr );
	SafeDelete( m_pEffectMngr );
	SafeRelease( m_pDefaultVertexDecl );
	SafeRelease( sm_pDevice );
	SafeRelease( m_pD3D );

	SafeRelease( m_pD3D );

	return( true );

}
/*
*	Clears the back buffer
*/
void CDX9Renderer::Clear( const uint32 _uColour, float32 _fDepth )
{
	sm_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, static_cast<D3DCOLOR>(_uColour), _fDepth, 0);
}
//Notifies and sets up the renderer for rendering
bool CDX9Renderer::BeginScene( )
{
	IRendererInterface::BeginScene( );
	if( FAILED( sm_pDevice->BeginScene( ) ) )
	{
		// assert 
		return false;
	}
	return true;
}
//Notifies and sets up the renderer for rendering
bool CDX9Renderer:: EndScene( )
{
	IRendererInterface::EndScene( );
	sm_pDevice->EndScene( );
	
	if( FAILED( sm_pDevice->Present( 0, 0, 0, 0 ) ) )
	{
		// assert
		assert_now( "Failed to present the DirectX scene!" );
		return false;
	}
	return true;
}

/*
*	Renders an array of user defined primitives
*	Param _kePrimitiveType	: The type of primitives to render as
*	Param _kuPrimitiveCount : The number of primitives to render
*	Param _kuVertexStride	: The sizeof each vertex being rendered
*	Param _kpVertices		: The array of vertices to render
*	Retun : Success
*/
bool CDX9Renderer::DrawPrimitivesUP( const EPrimitiveTypes _kePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride, const void* _kpVertices)
{

// Look up table for the DirectX Primitive types

	static const D3DPRIMITIVETYPE pPrimitiveTypes[] = 
	{
		D3DPT_TRIANGLELIST, //PT_TraingleList = 0,
		D3DPT_TRIANGLESTRIP,//PT_TriangleStrip,
		D3DPT_TRIANGLEFAN,	//PT_TriangleFan,
		D3DPT_LINELIST,		//PT_LineList,
		D3DPT_LINESTRIP,	//PT_LineStrip,
	};

	if( _kePrimitiveType == PT_QaudList )
	{
		return DrawQuadsUP( _kuPrimitiveCount, _kuVertexStride, _kpVertices );
	}

	if( FAILED( sm_pDevice->DrawPrimitiveUP( pPrimitiveTypes[ _kePrimitiveType ], _kuPrimitiveCount, _kpVertices, _kuVertexStride ) ) )
	{
		// DrawPrimitiveUp Failed to draw
		assert_now( "DrawPrimitiveUP Failed!" );
		return false;
	}

	return true;
	
}

/*
*	Renders an array of user defined verticies, using an array of user defines indices
*	Param _ePrimitiveType	: The type of primitive to render as
*	Param _kuPrimitiveCount	: The number of primitive to render
*	Param _kuVertexStride	: The size of each vertex being rendered
*	Param _pIndices			: The array of indices into the vertex array
*	Param _pVertices		: The array of vertices to render
*	Return : Success
*/
bool CDX9Renderer::DrawIndexedPrimitivesUP( const EPrimitiveTypes _ePrimitiveType, const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpIndices, const void* _kpVertices )
{
	// Look up table for the DirectX Primitive types

	static const D3DPRIMITIVETYPE pPrimitiveTypes[] = 
	{
		D3DPT_TRIANGLELIST, //PT_TraingleList = 0,
		D3DPT_TRIANGLESTRIP,//PT_TriangleStrip,
		D3DPT_TRIANGLEFAN,	//PT_TriangleFan,
		D3DPT_LINELIST,		//PT_LineList,
		D3DPT_LINESTRIP,	//PT_LineStrip,
	};

	uint32 pVertexCounts[]= 
	{	
		_kuPrimitiveCount * 3,	//PT_TraingleList = 0,
		0,						//PT_TriangleStrip,
		0,						//PT_TriangleFan,
		_kuPrimitiveCount * 2,	//PT_LineList,
		0,						//PT_LineStrip,
	};

	if( FAILED( sm_pDevice->DrawIndexedPrimitiveUP( pPrimitiveTypes[_ePrimitiveType], 0, pVertexCounts[_ePrimitiveType], _kuPrimitiveCount, _kpIndices, D3DFMT_INDEX32, _kpVertices, _kuVertexStride ) ) )
	{
		//assert
		assert_now( "Failed to draw indexed primitives!" );
		return false;
	}
	return true;
}

/*
*	Renders an array of quads
*	Param _kuPrimitiveCount	: The number of primitive to render
*	Param _kuVertexStride	: The size of each vertex being rendered
*	Param _pVertices		: The array of vertices to render
*	Return : Success
*/
bool CDX9Renderer::DrawQuadsUP( const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpVertices )
{
	static SXyzColourUV pQuads[1000];
	const SXyzColourUV* pVertices = reinterpret_cast<const SXyzColourUV* >( _kpVertices );

	uint32 uIndex = 0;
	for( uint32 i = 0; i < _kuPrimitiveCount; i += 4 )
	{
		pQuads[uIndex++] = pVertices[i];
		//pQuads[uIndex++] = pVertices[i + 1];
		//pQuads[uIndex++] = pVertices[i + 2];
		pQuads[uIndex++] = pVertices[i + 2];
		pQuads[uIndex++] = pVertices[i + 1];


		pQuads[uIndex++] = pVertices[i];
		//pQuads[uIndex++] = pVertices[i + 2];
		//pQuads[uIndex++] = pVertices[i + 3];
		pQuads[uIndex++] = pVertices[i + 3];
		pQuads[uIndex++] = pVertices[i + 2];

	}

	if( FAILED( sm_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, _kuPrimitiveCount * 2, pQuads, _kuVertexStride ) ) )
	{
		// DrawPrimitiveUp Failed to draw
		assert_now( "Failed to dr aw quads!" );
		return false;
	}

	return true;

}

/*
*	Renders primitives from a set vertex buffer
*	Param _kePrimitiveType	: The type of primitives to render
*	Param _kuPrimitiveCount : The number of primitives to render
*	Return : Success
*/
bool CDX9Renderer::DrawPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount )
{
	// Look up table for the DirectX Primitive types
	static const D3DPRIMITIVETYPE pPrimitiveTypes[] = 
	{
		D3DPT_TRIANGLELIST, //PT_TraingleList = 0,
		D3DPT_TRIANGLESTRIP,//PT_TriangleStrip,
		D3DPT_TRIANGLEFAN,	//PT_TriangleFan,
		D3DPT_LINELIST,		//PT_LineList,
		D3DPT_LINESTRIP,	//PT_LineStrip,
	};

	if( FAILED( sm_pDevice->DrawPrimitive( pPrimitiveTypes[_ePrimitiveType], 0, _kuPrimitiveCount ) ) )
	{
		assert_now( "Faild to draw primitives!" );
		return false;
	}
	return true;
}

/*
*	Renders primitives from a set vertex buffer using a set index buffer
*	Param _kePrimitiveType	: The type of primitives to render
*	Param _kuPrimitiveCount	: The number of primitiives to render
*	Return : Success
*/
bool CDX9Renderer::DrawIndexedPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexCount )
{
		// Look up table for the DirectX Primitive types
	static const D3DPRIMITIVETYPE pPrimitiveTypes[] = 
	{
		D3DPT_TRIANGLELIST, //PT_TraingleList = 0,
		D3DPT_TRIANGLESTRIP,//PT_TriangleStrip,
		D3DPT_TRIANGLEFAN,	//PT_TriangleFan,
		D3DPT_LINELIST,		//PT_LineList,
		D3DPT_LINESTRIP,	//PT_LineStrip,
	};

	
	if( FAILED( sm_pDevice->DrawIndexedPrimitive( pPrimitiveTypes[_ePrimitiveType], 0, 0, _kuVertexCount, 0, _kuPrimitiveCount ) ) )
	{
		assert_now( "Faild to draw indexed primitives!" );
		return false;
	}
	return true;
}

// State changes 

/*
*	Sets a transformation on the renderer
*	Param _kmTransform 		: The matrix that defines the transform
*	Param _keTransformType  : Defines the type of transform ( ETransform )
*	Param _kuStage			: The target stage for the transform
*/
void CDX9Renderer::SetTransform( const CFMat4x4& _kmTransform, const ETransforms _keTransformType, const uint32 _kuStage )
{
	UNUSED_VAR( _kuStage );
	static const D3DTRANSFORMSTATETYPE pTransforms[] =
	{
		D3DTS_WORLD,      //	TM_World
		D3DTS_VIEW,		  //	TM_View		
		D3DTS_PROJECTION, // 	TM_Projection
	};

	static CFMat4x4* pMatrixTransforms[] = 
	{
		&m_mWorldTransform,
		&m_mViewTransform,
		&m_mProjectionTRansform,
	};
	*pMatrixTransforms[_keTransformType] = _kmTransform;

	sm_pDevice->SetTransform( pTransforms[_keTransformType], reinterpret_cast< const D3DXMATRIX* >( &_kmTransform ) );

	return;
}

		/**
 *	Param _rmTransform 		: To be populated with the transform.
 *	Param _keTransformType  : Defines the type of transform ( ETransform )
 *	Param _kuStage			: The target stage for the transform
 */
void CDX9Renderer::GetTransform( CFMat4x4& _rmTransform, const ETransforms _keTransformType, const uint32 _kuStage  )
{
	static CFMat4x4* pTransforms[] = 
	{
		&m_mWorldTransform,
		&m_mViewTransform,
		&m_mProjectionTRansform,
	};
	_rmTransform = *pTransforms[_keTransformType];
}

/*
*	Sets a render state on the renderer
*	Param _keRenderState	: The render state to set
*	Param _kuValue			: The value to set
*/
//template< typename t>
void CDX9Renderer::SetRenderState( const ERenderStates _keRenderState, const uint32 _kuValue)
{
	// store a copy of the value.
	uint32 uValue = _kuValue;
	
	// Look up table for the DirectX renderstates.
	static const D3DRENDERSTATETYPE pRenderStates[] = 
	{
		D3DRS_LIGHTING,				// RS_Lighting.
		D3DRS_ZFUNC,			
		D3DRS_ALPHABLENDENABLE,
		D3DRS_CULLMODE,
		D3DRS_FILLMODE,
	};
	
	// Look up table for the cullmode states.
	static const D3DCULL pCullStates[] = 
	{
		D3DCULL_NONE,		// CM_NOCULL.
		D3DCULL_CW,			// CM_CW
		D3DCULL_CCW,		// CM_CCW
	};

	// look up table for fill modes
	static const D3DFILLMODE pFillModes[] = 
	{
		D3DFILL_WIREFRAME, // FM_WIREFRAME
		D3DFILL_SOLID,	   // FM_SOLID
		D3DFILL_POINT,	   // FM_POINTS
	};
	// If the state is a cull mode get the target state.
	if( _keRenderState == RS_CULLMODE )
	{
		uValue = pCullStates[_kuValue];
	}

	if( _keRenderState == RS_FILLMODE )
	{
		uValue = pFillModes[_kuValue];
	}


	sm_pDevice->SetRenderState( pRenderStates[_keRenderState], uValue );

	return;
}
/*
*	Initialise the dirtect x sdk and rendering device
*/
void CDX9Renderer::InitialiseDirectX( )
{

	D3DDISPLAYMODE D3DDM;	// Create a display mode structure.
	ZeroMemory(&D3DDM, sizeof(D3DDM));

	D3DCAPS9 D3DCaps;	// Create a device capability structure.
	ZeroMemory(&D3DCaps, sizeof(D3DCaps));

	D3DPRESENT_PARAMETERS D3DPP;	// Create a present parameters structure.
	ZeroMemory(&D3DPP, sizeof(D3DPP));

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	// Initiate COM layer transaction and get pointer to top level IDirect3D interface.

	if( NULL == m_pD3D )
	{
		// assert 
		int i = 0; i;
	}

	Validate(m_pD3D);	// If Direct3DCreate9() fails, exit out.	

	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DDM);	// Populate the display mode structure.

	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &D3DCaps);	// Populate the device capability structure.

	DWORD dwBehaviourFlags = 0;

	if (D3DCaps.VertexProcessingCaps != 0)	// Set vertex processing behavior flags.
	{
		dwBehaviourFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE; 
	}
	else
	{
		dwBehaviourFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}

	uint32 dwPresInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// Set the present interval.

	//if (_bCapFps)
	//{
	//	dwPresInterval = D3DPRESENT_INTERVAL_ONE; 
	//}

	if (m_pRendererContext->IsFullScreen( ))
	{
		m_pRendererContext->SetDisplayWidth( D3DDM.Width );
		m_pRendererContext->SetDisplayHeight( D3DDM.Height) ;	
	}

	HWND hWnd = *reinterpret_cast< HWND* >( m_pRendererContext->GetWindowHandle( ) );


	D3DPP.PresentationInterval		= dwPresInterval;						// Setup present parameters.
	D3DPP.BackBufferWidth 			= m_pRendererContext->GetDisplayWidth( );
	D3DPP.BackBufferHeight			= m_pRendererContext->GetDisplayHeight( );
	D3DPP.BackBufferFormat			= D3DDM.Format;
	D3DPP.BackBufferCount			= 1;
	D3DPP.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	D3DPP.hDeviceWindow				= hWnd;
	D3DPP.Windowed					= !m_pRendererContext->IsFullScreen( );
	D3DPP.EnableAutoDepthStencil	= true;
	D3DPP.AutoDepthStencilFormat	= D3DFMT_D16;
																			// And finally, create our Rendering Device.
	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwBehaviourFlags, &D3DPP, &sm_pDevice);
	if( NULL == sm_pDevice )
	{
		// assert 
		assert_now( "Failed to create the DirectX devicxe!" );
		int i = 0;i;
	}
}

/*
*	The following are managers assocuated wih rendering functionality!.
*/
// Returns the instance of tehe vertex declaration manager
IVertexDeclarationManager* CDX9Renderer::GetDeclarationManager( ) const
{
	return m_pDeclManager;
}
//Returns the instance of the texture manager implementation
ITextureManager* CDX9Renderer::GetTextureManager( ) const
{
	return m_pTextureMngr;
}
//Returs the instance of the light manager implementation
ILightManager* CDX9Renderer::GetLightManager( ) const
{
	return m_pLightMngr;
}

//Returs the instance of the material manager implementation
IMaterialManager* CDX9Renderer::GetMaterialManager( ) const
{
	return m_pMaterialMngr;
}
// Returns the instance of the effect manager implementation
IEffectManager* CDX9Renderer::GetEffectManager( )
{
	return m_pEffectMngr;
}

// 
IVertexBufferManager* CDX9Renderer::GetVertexBufferManager( )
{
	return m_pVertexBufferMngr;
}

/*
*	Creates a windo and sets up the main game loop
*/
bool CDX9Renderer::CreateRenderContext( IRendererContext* _pRendererContex )
{
	m_pRendererContext = _pRendererContex;
	//HINSTANCE hInstance = *reinterpret_cast< HINSTANCE* >( m_pRendererContext->GetInstance( ) );
	HINSTANCE hInstance = NULL;

	
	LPWSTR pName = (LPWSTR)m_pRendererContext->GetContextName( );

	// Create the window

	WNDCLASSEX winclass;
	bool bSuccess	= true;

	winclass.cbSize			= sizeof(WNDCLASSEX);
	winclass.style			= CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	if( hInstance )
	{
		winclass.hInstance		= hInstance;
	}
	else
	{
		winclass.hInstance = GetModuleHandle( NULL );
	}
	
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= pName,
	winclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		return (false);	// Failed to register.
	}

	// Get the menu
	const char* kpcMenuId = NULL;
	HMENU* pMenu = reinterpret_cast< HMENU* >( m_pRendererContext->GetWindowMenu( kpcMenuId ) ); 

	//Resize window?
	RECT rc = { 0, 0, m_pRendererContext->GetDisplayWidth(), m_pRendererContext->GetDisplayHeight() };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, false );

	HWND hWindow = CreateWindowEx(NULL,
								( LPWSTR ) m_pRendererContext->GetContextName( ),
								( LPWSTR ) m_pRendererContext->GetContextName( ),
								WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, 
								CW_USEDEFAULT,
								rc.right - rc.left, 
								rc.bottom - rc.top, 
								NULL,
								pMenu ? *pMenu : NULL,
								hInstance,
								NULL);
	if(!hWindow)
	{
//	assert_now( "Failed to craete the window" );
		return bSuccess;
	}

	m_pRendererContext->SetWindowHndle( reinterpret_cast< void* >( &hWindow ) );
	
	InitialiseDirectX( );

	// Create the managers 

	m_pDeclManager  = new CDX9VertexDeclarationManager( );
	m_pTextureMngr  = new CDX9TextureManager( );
	m_pLightMngr    = new CDX9LightManager( );
	m_pMaterialMngr = new CDX9MaterialManager( );
	m_pEffectMngr   = new CDX9EffectManager( );
	m_pVertexBufferMngr = new CDX9VertexBufferManager( );
	m_pRenderEffectMngr = new CRenderEffectManager( );

	return bSuccess;
	
}
/*
*	Runs the game loop
*/
sint32 CDX9Renderer::RunGameLoop( )
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if( false ==  m_pRendererContext->FrameUpdate( ) )
			{
				break;
			}
		}
	}

	return (static_cast<int>(msg.wParam));
}

/*
*	Microsoft cal back proc for a window
*/
LRESULT CALLBACK 
CDX9Renderer::WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return (0);
		}
		break;
	case WM_COMMAND:
		{
			// Fire the command to the renderer context.
			//m_pRendererContext->OnWindowCommand( _msg, _wparam, _lparam );
		}
		break;
	default:
		break;
	}

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}