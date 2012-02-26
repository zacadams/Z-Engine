/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLRenderer.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes 



#include "CoreLib/Core.h" 
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>

#include "RendererLib/RendererContext.h"
// Maths 
#include "MathLib/FMat4x4.h"

// Vertex

#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexElement.h"

#include "GLVertexDeclarationManager.h"

// Lights 

#include "RendererLib/LightManager.h"
#include "GLLightManager.h"

// Materials 

#include "RendererLib/MaterialManager.h"
#include "GLMaterialManager.h"

#include "GLRenderer.h"

using namespace ZGE;
CGLRenderer::CGLRenderer(void)
: m_pLightMngr( NULL )
{
	m_mWorldMatrix.Identity( );
	m_mViewMatrix.Identity( );
	m_mProjectionMatrix.Identity( );
	m_mScreenSpaceProjection.Identity( );
}

CGLRenderer::~CGLRenderer(void)
{
	
}
/*
*	Added to enfore the deletion and clean up of the rendering system 
*/
bool CGLRenderer::ShutDown( )
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( m_hRC );
	ReleaseDC( m_hWnd, m_hDC );

	SafeDelete( m_pDeclManager );
	return false;
}


//Clears the back buffer
void CGLRenderer::Clear( const uint32 _uColour, float32 f_Depth )
{

	static uint32  uClearColour = 0x00000000;
	
	// Only set the colour if it is different from the previous colour
	if( _uColour != uClearColour )
	{
		float32 pColour[4];
		ConvertColorToFloat( _uColour, pColour ); 
		glClearColor( pColour[1], pColour[2], pColour[3], pColour[0] );
		uClearColour = _uColour;
	}

	static float32 fDepth = 0.0f;
	// Clear the buffer
	if ( f_Depth != fDepth )
	{
		glClearDepth( fDepth );
		fDepth = f_Depth;
	}

	//Clear the color and depth buffers.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
//Notifies and sets up the renderer for rendering
bool CGLRenderer::BeginScene( )
{
	return true;
}
//Notifies and sets up the renderer for rendering
bool CGLRenderer::EndScene( )
{
	SwapBuffers( m_hDC );
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
bool CGLRenderer::DrawPrimitivesUP(	const EPrimitiveTypes _kePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride, const void* _kpVertices)
{

	static const  GLenum pPrimitiveTypes[] = 
	{
		GL_TRIANGLES, //PT_TraingleList = 0,
		GL_TRIANGLE_STRIP,//PT_TriangleStrip,
		GL_TRIANGLE_FAN,	//PT_TriangleFan,
		GL_LINE,		//PT_LineList,
		GL_LINE,	//PT_LineStrip,
	};
	// Vertex counts for different primitive types
	uint32 pVertexCounts[]= 
	{	
		_kuPrimitiveCount * 3,	//PT_TraingleList = 0,
		0,						//PT_TriangleStrip,
		0,						//PT_TriangleFan,
		_kuPrimitiveCount * 2,	//PT_LineList,
		0,						//PT_LineStrip,
	};
	uint32 uVertexCount = pVertexCounts[_kePrimitiveType];
	// Start rendering

	CVertexDescription* Desc = &m_pDeclManager->GetActiveDeclaration( )->GetDescription( );

	// Is this being rendered stright to screen space?
	CVertexElement VE;
	bool bDrawnToScreenSpace = false;
	if( Desc->GetElement( CVertexElement::ES_POSITIONT, VE ) )
	{
		// POSITIONT: Renders to screen space.
		// Set the projection to be screen space.
		// Set the world view matrix to be identity
		bDrawnToScreenSpace = true;

		// Set the projection matrix
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( reinterpret_cast< float32* >( &m_mScreenSpaceProjection ) );
		
		// Set the world / view matrix
		glMatrixMode( GL_MODELVIEW );
		CFMat4x4 mIdentity;
		mIdentity.Identity( );
		glLoadMatrixf( reinterpret_cast< float32* >( &mIdentity ) );
	}

	glBegin( pPrimitiveTypes[_kePrimitiveType] );

	// Draw the vertices
	// All vertex data must be set before the
	// glVertex call. The glVertexCall renders a vertex so its data has to be set first
	for( uint32 i = 0; i < uVertexCount; ++i )
	{
		
		if( Desc->GetElement( CVertexElement::ES_COLOUR, VE ) )
		{
			// Extract colour
			uint32 uColourOffSet = VE.GetOffset( );
			uint32 uOffset = ( i * _kuVertexStride ) + uColourOffSet;
			const uint32* pData = reinterpret_cast< const uint32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
			
			float32 pColour[4];
			ConvertColorToFloat( *pData, pColour );
			// extract the data, RGBA
			glColor4f( pColour[1], pColour[2], pColour[3], pColour[0] );

		}

		if( Desc->GetElement( CVertexElement::ES_NORMAL, VE ) )
		{
			// Extract the normals
			uint32 uNormalOffSet = VE.GetOffset( );
			// 3 floats 12 bytes
			uint32 uOffset = ( i * _kuVertexStride ) + uNormalOffSet;
			const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
			
			// extract the data
			glNormal3f( pData[0], pData[1], pData[2] );
		}
		
		if( Desc->GetElement( CVertexElement::ES_TEXCOORD, VE ) )
		{
			// Extract uv coordinates
			uint32 uTexOffSet = VE.GetOffset( );
			uint32 uOffset = ( i * _kuVertexStride ) + uTexOffSet;
			const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
			
			// extract the data
			glTexCoord2f( pData[0], pData[1] );
		}

		// Assuming the position will be the first element
		//Position, extract the position data
		uint32 uPositionOffSet = 0;
		//3 floats 12 bytes
				
		uint32 uOffset = ( i * _kuVertexStride ) + uPositionOffSet;
		const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
		
		// extract the data
		glVertex3f( pData[0], pData[1], pData[2] );

		// finaly draw the vertex

		//// Set the vertex data 
		//for( uint32 j = 0; j < Desc->GetElementCount( ); ++j )
		//{
		////	CVertexElement VE = Desc->GetElement( j );
		//	VE = Desc->GetElement( j );
		//	switch( VE.GetSemantic( ) )
		//	{
		//		case CVertexElement::ES_POSITIONT:
		//		case CVertexElement::ES_POSITION:	// Fall through
		//			{
		//				// Position, extract the position data
		//				uint32 uPositionOffSet = VE.GetOffset( );
		//				// 3 floats 12 bytes
		//				
		//				uint32 uOffset = ( i * _kuVertexStride ) + uPositionOffSet;
		//				const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
		//				
		//				// extract the data
		//				glVertex3f( pData[0], pData[1], pData[2] );
		//			}
		//			break;
		//		case CVertexElement::ES_NORMAL:
		//			{
		//				// Extract the normals
		//				uint32 uNormalOffSet = VE.GetOffset( );
		//				// 3 floats 12 bytes
		//				uint32 uOffset = ( i * _kuVertexStride ) + uNormalOffSet;
		//				const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
		//				
		//				// extract the data
		//				glNormal3f( pData[0], pData[1], pData[2] );
		//			}
		//			break;
		//		case CVertexElement::ES_TEXCOORD:
		//			{
		//				// Extract uv coordinates
		//				uint32 uTexOffSet = VE.GetOffset( );
		//				uint32 uOffset = ( i * _kuVertexStride ) + uTexOffSet;
		//				const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
		//				
		//				// extract the data
		//				glTexCoord2f( pData[0], pData[1] );
		//			}
		//			break;
		//		case CVertexElement::ES_COLOUR:
		//			{
		//				// Extract colour
		//				uint32 uColourOffSet = VE.GetOffset( );
		//				uint32 uOffset = ( i * _kuVertexStride ) + uColourOffSet;
		//				const uint32* pData = reinterpret_cast< const uint32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffset );
		//				
		//				float32 pColour[4];
		//				ConvertColorToFloat( *pData, pColour );
		//				// extract the data, RGBA
		//				glColor4f( pColour[1], pColour[2], pColour[3], pColour[0] );

		//				if( pColour[0] != 1.0f &&
		//					pColour[1] != 0.0f &&
		//					pColour[2] != 0.0f &&
		//					pColour[3] != 0.0f )
		//				{
		//					int i = 0;i;
		//				}

		//			}
		//			break;
		//		default:assert_now( "UNKNOWN SEMANTIC!" );
		//	}
			// Get the vertex's colour
		//}
	}
	
	
	// Finish rendering
	glEnd( );

	glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );

	//Note: if we have just drawnto screen space,
	// we will need to set original projection matrix
	// so th at all 3d objects get rendered properly.

	if( bDrawnToScreenSpace )
	{
		//SetTransform( m_mWorld, TM_View, 0 );
		SetTransform( m_mProjectionMatrix, TM_Projection, 0 );
	}

	return false;
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
bool CGLRenderer::DrawIndexedPrimitivesUP( const EPrimitiveTypes _kePrimitiveType, const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpIndices, const void* _kpVertices )
{
	
	static const  GLenum pPrimitiveTypes[] = 
	{
		GL_TRIANGLES, //PT_TraingleList = 0,
		GL_TRIANGLE_STRIP,//PT_TriangleStrip,
		GL_TRIANGLE_FAN,	//PT_TriangleFan,
		GL_LINE,		//PT_LineList,
		GL_LINE,	//PT_LineStrip,
	};
	// Vertex counts for different primitive types
	uint32 pVertexCounts[]= 
	{	
		_kuPrimitiveCount * 3,	//PT_TraingleList = 0,
		0,						//PT_TriangleStrip,
		0,						//PT_TriangleFan,
		_kuPrimitiveCount * 2,	//PT_LineList,
		0,						//PT_LineStrip,
	};
	uint32 uVertexCount = pVertexCounts[_kePrimitiveType];
	// Start rendering

	CVertexDescription* Desc = &m_pDeclManager->GetActiveDeclaration( )->GetDescription( );

	// Is this being rendered stright to screen space?
	CVertexElement VE;
	bool bDrawnToScreenSpace = false;
	if( Desc->GetElement( CVertexElement::ES_POSITIONT, VE ) )
	{
		// POSITIONT: Renders to screen space.
		// Set the projection to be screen space.
		// Set the world view matrix to be identity
		bDrawnToScreenSpace = true;

		// Set the projection matrix
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( reinterpret_cast< float32* >( &m_mScreenSpaceProjection ) );
		
		// Set the world / view matrix
		glMatrixMode( GL_MODELVIEW );
		CFMat4x4 mIdentity;
		mIdentity.Identity( );
		glLoadMatrixf( reinterpret_cast< float32* >( &mIdentity ) );
	}

	// Initialise variables
	uint32 uOffSet = 0;

	glBegin( pPrimitiveTypes[_kePrimitiveType] );

	const uint32* pIndices = reinterpret_cast< const uint32* >( _kpIndices );

	// Draw the vertices
	// All vertex data must be set before the
	// glVertex call. The glVertexCall renders a vertex so its data has to be set first
	for( uint32 i = 0; i < uVertexCount; ++i )
	{
		// Use the index to get the nedded vertex
		uint32 uIndex = pIndices[i];
		if( Desc->GetElement( CVertexElement::ES_COLOUR, VE ) )
		{
			// Extract colour
			uOffSet = VE.GetOffset( );
			uOffSet = ( uIndex * _kuVertexStride ) + uOffSet;
			const uint32* pData = reinterpret_cast< const uint32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffSet );
			
			float32 pColour[4];
			ConvertColorToFloat( *pData, pColour );
			// extract the data, RGBA
			glColor4f( pColour[1], pColour[2], pColour[3], pColour[0] );

		}

		if( Desc->GetElement( CVertexElement::ES_NORMAL, VE ) )
		{
			// Extract the normals
			uOffSet = VE.GetOffset( );
			// 3 floats 12 bytes
			uOffSet= ( uIndex * _kuVertexStride ) + uOffSet;
			const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffSet );
			
			// extract the data
			glNormal3f( pData[0], pData[1], pData[2] );
		}
		
		if( Desc->GetElement( CVertexElement::ES_TEXCOORD, VE ) )
		{
			// Extract uv coordinates
			uOffSet = VE.GetOffset( );
			uOffSet= ( uIndex * _kuVertexStride ) + uOffSet;
			const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffSet );
			
			// extract the data
			glTexCoord2f( pData[0], pData[1] );
		}

		// Assuming the position will be the first element
		//Position, extract the position data
		uOffSet = 0;
		//3 floats 12 bytes
				
		uOffSet = ( uIndex * _kuVertexStride ) + uOffSet;
		const float32* pData = reinterpret_cast< const float32* >( reinterpret_cast< const BYTE* >( _kpVertices ) + uOffSet );
		
		// extract the data
		glVertex3f( pData[0], pData[1], pData[2] );
	}
	
	
	// Finish rendering
	glEnd( );

	glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );

	//Note: if we have just drawnto screen space,
	// we will need to set original projection matrix
	// so th at all 3d objects get rendered properly.

	if( bDrawnToScreenSpace )
	{
		//SetTransform( m_mWorld, TM_View, 0 );
		SetTransform( m_mProjectionMatrix, TM_Projection, 0 );
	}



	return false;
}
// State changes 

/*
*	Sets a transformation on the renderer
*	Param _kmTransform 		: The matrix that defines the transform
*	Param _keTransformType  : Defines the type of transform ( ETransform )
*	Param _kuStage			: The target stage for the transform
*/
void CGLRenderer::SetTransform( const CFMat4x4& _kmTransform, const ETransforms _keTransformType, const uint32 _kuStage )
{	

	UNUSED_VAR( _kuStage );

	CFMat4x4 mTempMatrix = _kmTransform;

	if( _keTransformType == TM_World )
	{
		m_mWorldMatrix = _kmTransform;
		////Premultiply by view matrix.
		CFMat4x4 mView = m_mViewMatrix;
		mView *= CFMat4x4::CreateScaleMatrix( CFVec3( 1.0f, 1.0f, -1.0f ) );
		mTempMatrix *= m_mViewMatrix;

		//// Select the model view matrix stack
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( reinterpret_cast< float32* >( &mTempMatrix ) );
		//
		////Get current matrix stack depth.
		//sint32 iStackDepth = 0;
		//glGetIntegerv( GL_MODELVIEW_STACK_DEPTH, &iStackDepth );
		//uint32 uStackDepth = static_cast< uint32 >( iStackDepth );

		////Pop any previous matrices off the stack!
		//while ( uStackDepth > _kuStage )
		//{
		//	glPopMatrix();
		//	--uStackDepth;
		//}

		////Push new world matrix on to the stack.
		//glLoadIdentity();
		//glLoadMatrixf( reinterpret_cast<float32*>( &mTempMatrix ) ); 

	}
	else if( _keTransformType == TM_View )
	{
	//	//Need to scale by -1 in Z direction
		//mTempMatrix *= CFMat4x4::CreateScaleMatrix( CFVec3( 1.0f, 1.0f, -1.0f ) );
	//	
	//	//Save as new view matrix.
		m_mViewMatrix = mTempMatrix;
	}
	else if ( _keTransformType == TM_Projection )
	{
	//	
	//	//We expect a left-handed perspective matrix, GL expects right-handed.
	//	//Convert projection to right handed:
		//mTempMatrix.LHToRHProjection( );
	//	//mTempMatrix.Set( 2, 3, -1.0f );
	//	//mTempMatrix.Set( 3, 2, mTempMatrix.Get(3,2) * -1.0f );
		m_mProjectionMatrix = _kmTransform;
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( reinterpret_cast< float32* >( &mTempMatrix ) );
	//	
		////Get current matrix stack depth.
		//sint32 iStackDepth = 0;
		//glGetIntegerv( GL_PROJECTION_STACK_DEPTH, &iStackDepth );
		//
		//uint32 uStackDepth = static_cast< uint32 >( iStackDepth );
		////Pop any previous matrices off the stack - want to work with an empty stack:
		//while ( uStackDepth > 0 )
		//{
		//	glPopMatrix();
		//	--uStackDepth;
		//}

		//glLoadIdentity();

		////Push new projection matrix on to the stack.
		//glLoadMatrixf( reinterpret_cast<float32*>( &mTempMatrix ) ); 
	}

	//glDisableClientState( GL_VERTEX_ARRAY );


}
/*
*	Sets a render state on the renderer
*	Param _keRenderState	: The render state to set
*	Param _kuValue			: The value to set
*/
//template< typename t>
void CGLRenderer::SetRenderState( const ERenderStates _keRenderState, const uint32 _kuValue)
{
	UNUSED_VAR( _keRenderState );
	UNUSED_VAR( _kuValue );
	assert_now( "Un implemented" );
}

//// Buffered Draw calls

/*
*	Renders primitives from a set vertex buffer
*	Param _kePrimitiveType	: The type of primitives to render
*	Param _kuPrimitiveCount : The number of primitives to render
*	Return : Success
*/
bool CGLRenderer::DrawPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount )
{
	UNUSED_VAR( _ePrimitiveType );
	UNUSED_VAR( _kuPrimitiveCount );
	assert_now( "Un implemented" );
	return false;
}
/*
*	Renders primitives from a set vertex buffer using a set index buffer
*	Param _kePrimitiveType	: The type of primitives to render
*	Param _kuPrimitiveCount	: The number of primitiives to render
*	Return : Success
*/
bool CGLRenderer::DrawIndexedPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexCount )
{
	UNUSED_VAR( _ePrimitiveType );
	UNUSED_VAR( _kuPrimitiveCount );
	UNUSED_VAR( _kuVertexCount );
	assert_now( "Un implemented" );
	return false;
}


///*
//*	Renders primitives from a set vertex buffer using a set index buffer
//*	Param _kePrimitiveType	: The type of primitives to render
//*	Param _kuPrimitiveCount	: The number of primitiives to render
//*	Return : Success
//*/
//virtual bool DrawIndexedPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount ) = 0;


// Window creation

/*
*	Creates a windo and sets up the main game loop
*/
bool CGLRenderer::CreateRenderContext( IRendererContext* _pRendererContex )
{
	m_pRendererContext = _pRendererContex;
	HINSTANCE hInstance = *reinterpret_cast< HINSTANCE* >( m_pRendererContext->GetInstance( ) );
	

	
	LPWSTR pName = (LPWSTR)m_pRendererContext->GetContextName( );

	// Create the window

	WNDCLASSEX winclass;
	bool bSuccess	= true;

	winclass.cbSize			= sizeof(WNDCLASSEX);
	winclass.style			= CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hInstance;
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


	//Resize window?
	RECT rc = { 0, 0, m_pRendererContext->GetDisplayWidth(), m_pRendererContext->GetDisplayHeight() };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, false );

	HWND hWindow = CreateWindowEx(NULL,
								( LPWSTR ) m_pRendererContext->GetContextName( ),
								( LPWSTR ) m_pRendererContext->GetContextName( ),
								//lstrWindowTitle,
								//lstrWindowTitle,
								WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
								CW_USEDEFAULT, 
								CW_USEDEFAULT,
								rc.right - rc.left,
								rc.bottom - rc.top,
								//m_pRendererContext->GetDisplayWidth( ),
								//m_pRendererContext->GetDisplayHeight( ),
								NULL,
								NULL,
								hInstance,
								NULL);
	if(!hWindow)
	{
//	assert_now( "Failed to craete the window" );
		return false;
	}

	m_pRendererContext->SetWindowHndle( reinterpret_cast< void* >( &hWindow ) );

	// Initialise OpenGL
	InitialiseOpenGL( &hWindow );

	glClearDepth( 1.0f );

	//glEnable( GL_DEPTH_TEST );
	//glDepthFunc( GL_LEQUAL );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	
	//Set cullmode to CCW
	glEnable( GL_CULL_FACE );
	glFrontFace( GL_CW );
	glCullFace( GL_BACK );

	//Enable textures
	glEnable( GL_TEXTURE_2D );
	glShadeModel( GL_SMOOTH );

	//Set the lighting model:
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 0 );

	// Init viewport
	glViewport( 0, 0, m_pRendererContext->GetDisplayWidth(), m_pRendererContext->GetDisplayHeight() );

	// Set the projection and model view matrix to be identity

	//glMatrixMode( GL_PROJECTION );
	//glPushMatrix();
	///glLoadIdentity();

	// Set up the orthographic projection
	//gluOrtho2D( 0.0f, m_pRendererContext->GetDisplayWidth(), m_pRendererContext->GetDisplayHeight(), 0.0f );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_mScreenSpaceProjection = CFMat4x4::CreateOffSetOrthoProjectionMatrix( 0.0f, 
																			(float32)m_pRendererContext->GetDisplayWidth( ),
																			0.0f, 
																			(float32)m_pRendererContext->GetDisplayHeight( ),
																			-1.0f,
																			1.0f );

	//m_mScreenSpaceProjection.LHToRHProjection( );

	// Make sure depth testing and lighting are disabled for 2D rendering until
	// we are finished rendering in 2D
	//glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
	//glDisable( GL_DEPTH_TEST );
	//glDisable( GL_LIGHTING );


	m_pDeclManager = new CGLVertexDeclarationManager( );
	m_pLightMngr = new CGLLightManager( );
	m_pMaterialMngr = new CGLMaterialManager( );


	return bSuccess;
}
/*
*	Runs the game loop
*/
sint32 CGLRenderer::RunGameLoop( )
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

	ShutDown( ); 

	return (static_cast<int>(msg.wParam));
}

/*
*	Microsoft cal back proc for a window
*/
LRESULT CALLBACK 
CGLRenderer::WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return (0);
		}
		break;
	default:
		break;
	}

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

//Initialises OpenGL
void CGLRenderer::InitialiseOpenGL( HWND* _hWnd  )
{

	m_hWnd = *_hWnd;

	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
	m_hDC = GetDC( *_hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( m_hDC, &pfd );
	SetPixelFormat( m_hDC, format, &pfd );
	
	// create and enable the render context (RC)
	m_hRC = wglCreateContext( m_hDC );
	if( FALSE == wglMakeCurrent( m_hDC, m_hRC ) )
	{
		assert_now( "Failed to initialise OpenGL renderer!" );
		return;
	}
}

//	Managers

// Returns the instance of the vertex declaration manager
IVertexDeclarationManager* CGLRenderer::GetDeclarationManager( ) const
{
	return m_pDeclManager;
}

//Returs the instance of the texture manager implementation
ITextureManager* CGLRenderer::GetTextureManager( ) const
{
	return NULL;
}

//Returs the instance of the light manager implementation
ILightManager* CGLRenderer::GetLightManager( ) const
{
	return m_pLightMngr;
}

//Returs the instance of the material manager implementation
IMaterialManager* CGLRenderer::GetMaterialManager( ) const
{
	return m_pMaterialMngr;
}

// Returns the instance of the effect manager implementation
IEffectManager* CGLRenderer::GetEffectManager( )
{
	return NULL;
}


