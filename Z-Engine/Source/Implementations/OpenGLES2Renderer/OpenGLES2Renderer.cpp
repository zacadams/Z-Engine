#include "CoreLib/Core.h"
#ifdef WIN32
#include <stdio.h>
#include <windows.h>
#include <TCHAR.h>
#endif
// Inludes
#include <EGL/egl.h>
#include <GLES2/gl2.h>

// Renderer
#include "RendererLib/RendererContext.h"
#include "OpenGLES2Renderer/OpenGLESVertexDeclarationManager.h"

#include "OpenGLES2Renderer/OpenGLES2Renderer.h"
using namespace ZGE;
COpenGLES2Renderer::COpenGLES2Renderer(void)
{
}

COpenGLES2Renderer::~COpenGLES2Renderer(void)
{
}

/*
*	Added to enfore the deletion and clean up of the rendering system 
*/
bool COpenGLES2Renderer::ShutDown( )
{
	return false;
}


//Clears the back buffer
void COpenGLES2Renderer::Clear( const uint32 _uColour, float32 _fDepth )
{
	static float32 pColour[4];
	static uint32 uColour =0;
	if( _uColour != uColour )
	{
		ZUtilities::ConvertColorToFloatRGBA( _uColour, pColour );
		glClearColor(pColour[3], pColour[2], pColour[1], pColour[0]);
		uColour = _uColour;
	}

	static float32 fDepth = 0.0f;
	// Clear the buffer
	if ( _fDepth != fDepth )
	{
		glClearDepthf( fDepth );
		fDepth = _fDepth;
	}

	//Clear the color and depth buffers.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//Notifies and sets up the renderer for rendering
bool COpenGLES2Renderer::BeginScene( )
{
	return true;
}


//Notifies and sets up the renderer for rendering
bool COpenGLES2Renderer::EndScene( )
{
	//SwapBuffers( m_hDC );
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
bool COpenGLES2Renderer::DrawPrimitivesUP(	const EPrimitiveTypes _kePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride, const void* _kpVertices)
{
	// Loop through all the elements in the active vertex declaration.

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

	// Is this being rendered streight to screen space?
	CVertexElement VE;

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
	}
	
	// Finish rendering
	glEnd( );
	glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );

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
bool COpenGLES2Renderer::DrawIndexedPrimitivesUP( const EPrimitiveTypes _ePrimitiveType, const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpIndices, const void* _kpVertices )
{
	return false;
}

/*
*	Renders an array of quads
*	Param _kuPrimitiveCount	: The number of primitive to render
*	Param _kuVertexStride	: The size of each vertex being rendered
*	Param _pVertices		: The array of vertices to render
*	Return : Success
*/
bool COpenGLES2Renderer::DrawQuadsUP( const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpVertices )
{
	return false;
}

		/*
*	Renders primitives from a set vertex buffer
*	Param _kePrimitiveType	: The type of primitives to render
*	Param _kuPrimitiveCount : The number of primitives to render
*	Return : Success
*/
bool COpenGLES2Renderer::DrawPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount )
{
	return false;
}

/*
*	Renders primitives from a set vertex buffer using a set index buffer
*	Param _kePrimitiveType	: The type of primitives to render
*	Param _kuPrimitiveCount	: The number of primitiives to render
*	Return : Success
*/
bool COpenGLES2Renderer::DrawIndexedPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexCount )
{
	return false;
}

// State changes 

/*
*	Sets a transformation on the renderer
*	Param _kmTransform 		: The matrix that defines the transform
*	Param _keTransformType  : Defines the type of transform ( ETransform )
*	Param _kuStage			: The target stage for the transform
*/
void COpenGLES2Renderer::SetTransform( const CFMat4x4& _kmTransform, const ETransforms _keTransformType, const uint32 _kuStage )
{
}

		/**
 *	Param _rmTransform 		: To be populated with the transform.
 *	Param _keTransformType  : Defines the type of transform ( ETransform )
 *	Param _kuStage			: The target stage for the transform
 */
void COpenGLES2Renderer::GetTransform( CFMat4x4& _rmTransform, const ETransforms _keTransformType, const uint32 _kuStage  )
{
}

/*
*	Sets a render state on the renderer
*	Param _keRenderState	: The render state to set
*	Param _kuValue			: The value to set
*/
//template< typename t>
void COpenGLES2Renderer::SetRenderState( const ERenderStates _keRenderState, const uint32 _kuValue)
{
}
/*!****************************************************************************
 @Function		TestEGLError
 @Input			pszLocation		location in the program where the error took
								place. ie: function name
 @Return		bool			true if no EGL error was detected
 @Description	Tests for an EGL error and prints it
******************************************************************************/
bool TestEGLError(HWND hWnd, char* pszLocation)
{
	/*
		eglGetError returns the last error that has happened using egl,
		not the status of the last called function. The user has to
		check after every single egl call or at least once every frame.
	*/
	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS)
	{
#ifdef WIN32
		TCHAR pszStr[256];
		_stprintf(pszStr, _T("%s failed (%d).\n"), pszLocation, iErr);
		MessageBox(hWnd, pszStr, _T("Error"), MB_OK|MB_ICONEXCLAMATION);
#endif
		return false;
	}

	return true;
}


/*!****************************************************************************
 @Function		WndProc
 @Input			hWnd		Handle to the window
 @Input			message		Specifies the message
 @Input			wParam		Additional message information
 @Input			lParam		Additional message information
 @Return		LRESULT		result code to OS
 @Description	Processes messages for the main window
******************************************************************************/
#ifdef WIN32
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		// Handles the close message when a user clicks the quit icon of the window
		case WM_CLOSE:
			PostQuitMessage(0);
			return 1;

		default:
			break;
	}

	// Calls the default window procedure for messages we did not handle
	return DefWindowProc(hWnd, message, wParam, lParam);
}
#endif


/*
*	Creates a windo and sets up the main game loop
*/
bool COpenGLES2Renderer::CreateRenderContext( IRendererContext* _pRendererContex )
{
	m_pRendererContext  = _pRendererContex;
#ifdef WIN32
	// Create the game window.
	// Windows variables
	HWND				hWnd	= 0;
	HDC					hDC		= 0;
	HINSTANCE           hInstance = *reinterpret_cast< HINSTANCE* >( m_pRendererContext->GetInstance() );
	if( NULL == hInstance )
	{
		hInstance = GetModuleHandle( NULL );
	}
	LPWSTR pName = (LPWSTR)m_pRendererContext->GetContextName( );

#endif 
	

	// EGL variables
	EGLDisplay			eglDisplay	= 0;
	EGLConfig			eglConfig	= 0;
	EGLSurface			eglSurface	= 0;
	EGLContext			eglContext	= 0;
	EGLNativeWindowType	eglWindow	= 0;
	
	/*
		Step 0 - Create a EGLNativeWindowType that we can use for OpenGL ES output
	*/
#ifdef WIN32
	// Register the windows class
	WNDCLASS sWC;
    sWC.style = CS_HREDRAW | CS_VREDRAW;
	sWC.lpfnWndProc = WndProc;
    sWC.cbClsExtra = 0;
    sWC.cbWndExtra = 0;
    sWC.hInstance = hInstance;
    sWC.hIcon = 0;
    sWC.hCursor = 0;
    sWC.lpszMenuName = 0;
	sWC.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	sWC.lpszClassName =pName;
	unsigned int nWidth = m_pRendererContext->GetDisplayWidth();
	unsigned int nHeight = m_pRendererContext->GetDisplayHeight();

	ATOM registerClass = RegisterClass(&sWC);
	if (!registerClass)
	{
		MessageBox(0, _T("Failed to register the window class"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
	}

	// Create the eglWindow
/*
	RECT	sRect;
	SetRect(&sRect, 0, 0, nWidth, nHeight);
	AdjustWindowRectEx(&sRect, WS_CAPTION | WS_SYSMENU, false, 0);
	hWnd = CreateWindow( _T("Window"), _T("HelloTriangle"), WS_VISIBLE | WS_SYSMENU,
						 0, 0, nWidth, nHeight, NULL, NULL, hInstance, NULL);
	eglWindow = hWnd;
*/
	// my imp
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
	eglWindow = hWindow;
	

	
	// Get the associated device context
	hDC = GetDC(hWnd);
	if (!hDC)
	{
		MessageBox(0, _T("Failed to create the device context"), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		// clean up.
	}
#endif

	// Initialise the OpenGLES device.
	/*
		Step 1 - Get the default display.
		EGL uses the concept of a "display" which in most environments
		corresponds to a single physical screen. Since we usually want
		to draw to the main screen or only have a single screen to begin
		with, we let EGL pick the default display.
		Querying other displays is platform specific.
	*/
	eglDisplay = eglGetDisplay(hDC);

    if(eglDisplay == EGL_NO_DISPLAY)
	{
         eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
	}
	/*
		Step 2 - Initialize EGL.
		EGL has to be initialized with the display obtained in the
		previous step. We cannot use other EGL functions except
		eglGetDisplay and eglGetError before eglInitialize has been
		called.
		If we're not interested in the EGL version number we can just
		pass NULL for the second and third parameters.
	*/
	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
	{
#ifdef WIN32
		MessageBox(0, _T("eglInitialize() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
#endif
		return false;
		//goto cleanup;
	}

	/*
		Step 3 - Make OpenGL ES the current API.
		EGL provides ways to set up OpenGL ES and OpenVG contexts
		(and possibly other graphics APIs in the future), so we need
		to specify the "current API".
	*/
	eglBindAPI(EGL_OPENGL_ES_API);
	if (!TestEGLError(hWnd, "eglBindAPI"))
	{
		//goto cleanup;
	}

	/*
		Step 4 - Specify the required configuration attributes.
		An EGL "configuration" describes the pixel format and type of
		surfaces that can be used for drawing.
		For now we just want to use the default Windows surface,
		i.e. it will be visible on screen. The list
		has to contain key/value pairs, terminated with EGL_NONE.
	 */
	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,				0,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		EGL_DEPTH_SIZE,			EGL_DONT_CARE,
		EGL_NONE
	};

	/*
		Step 5 - Find a config that matches all requirements.
		eglChooseConfig provides a list of all available configurations
		that meet or exceed the requirements given as the second
		argument. In most cases we just want the first config that meets
		all criteria, so we can limit the number of configs returned to 1.
	*/
	int iConfigs;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
#ifdef WIN32
		MessageBox(0, _T("eglChooseConfig() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
#endif
		//goto cleanup;
	}

	/*
		Step 6 - Create a surface to draw to.
		Use the config picked in the previous step and the native window
		handle when available to create a window surface. A window surface
		is one that will be visible on screen inside the native display (or
		fullscreen if there is no windowing system).
		Pixmaps and pbuffers are surfaces which only exist in off-screen
		memory.
	*/
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);

    if(eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}

	if (!TestEGLError(hWnd, "eglCreateWindowSurface"))
	{
		//goto cleanup;
	}

	/*
		Step 7 - Create a context.
		EGL has to create a context for OpenGL ES. Our OpenGL ES resources
		like textures will only be valid inside this context
		(or shared contexts)
	*/
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
	if (!TestEGLError(hWnd, "eglCreateContext"))
	{
		//goto cleanup;
	}

	/*
		Step 8 - Bind the context to the current thread and use our
		window surface for drawing and reading.
		Contexts are bound to a thread. This means you don't have to
		worry about other threads and processes interfering with your
		OpenGL ES application.
		We need to specify a surface that will be the target of all
		subsequent drawing operations, and one that will be the source
		of read operations. They can be the same surface.
	*/
	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	if (!TestEGLError(hWnd, "eglMakeCurrent"))
	{
		//goto cleanup;
	}


	// Create the the engines rendering systems.
	m_pDeclManager = new COpenGLESVertexDeclarationManager( );


	return true;
}

/*
*	Runs the game loop
*/
sint32 COpenGLES2Renderer::RunGameLoop( )
{
	return 0;
}

//LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);



// Managers

// Returns the instance of tehe vertex declaration manager
 IVertexDeclarationManager* COpenGLES2Renderer::GetDeclarationManager( ) const 
{
	return m_pDeclManager;
}

//Returs the instance of the texture manager implementation
 ITextureManager* COpenGLES2Renderer::GetTextureManager( ) const
{
		return NULL;
}

//Returs the instance of the light manager implementation
 ILightManager* COpenGLES2Renderer::GetLightManager( ) const
{
		return NULL;
}

//Returs the instance of the material manager implementation
 IMaterialManager* COpenGLES2Renderer::GetMaterialManager( ) const
{
		return NULL;
}

// Returns the instance of the effect manager implementation
 IEffectManager* COpenGLES2Renderer::GetEffectManager( )
{
	return NULL;
}

		// Returns the vertex buffer manager.
 IVertexBufferManager* COpenGLES2Renderer::GetVertexBufferManager( )
{
	return NULL;
}

