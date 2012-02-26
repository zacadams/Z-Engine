/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLRenderer.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLRENDERER_H__Included_1682832923
#define _GLRENDERER_H__Included_1682832923

#include "RendererLib/RendererInterface.h"
#include "MathLib/FMat4x4.h"
#include "CoreLib/MemoryAlignment.h"
namespace ZGE
{
	class IVertexDeclaration;
	class IVertexDeclarationManager;
	class ILightManager;
	class IMaterialManager;

	_ALIGNED_PREFIX( 16 )
	class CGLRenderer : public IRendererInterface, public TAligned<16>
	{
	public:
		CGLRenderer(void);
		~CGLRenderer(void);

				/*
		*	Added to enfore the deletion and clean up of the rendering system 
		*/
		virtual bool ShutDown( );

	
		//Clears the back buffer
		virtual void Clear( const uint32 _uColour, float32 f_Depth ); 

		//Notifies and sets up the renderer for rendering
		virtual bool BeginScene( );

		
		//Notifies and sets up the renderer for rendering
		virtual bool EndScene( );

		/*
		*	Renders an array of user defined primitives
		*	Param _kePrimitiveType	: The type of primitives to render as
		*	Param _kuPrimitiveCount : The number of primitives to render
		*	Param _kuVertexStride	: The sizeof each vertex being rendered
		*	Param _kpVertices		: The array of vertices to render
		*	Retun : Success
		*/
		virtual bool DrawPrimitivesUP(	const EPrimitiveTypes _kePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride, const void* _kpVertices);

		/*
		*	Renders an array of user defined verticies, using an array of user defines indices
		*	Param _ePrimitiveType	: The type of primitive to render as
		*	Param _kuPrimitiveCount	: The number of primitive to render
		*	Param _kuVertexStride	: The size of each vertex being rendered
		*	Param _pIndices			: The array of indices into the vertex array
		*	Param _pVertices		: The array of vertices to render
		*	Return : Success
		*/
		virtual bool DrawIndexedPrimitivesUP( const EPrimitiveTypes _ePrimitiveType, const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpIndices, const void* _kpVertices );

				/*
		*	Renders primitives from a set vertex buffer
		*	Param _kePrimitiveType	: The type of primitives to render
		*	Param _kuPrimitiveCount : The number of primitives to render
		*	Return : Success
		*/
		virtual bool DrawPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount );

				/*
		*	Renders primitives from a set vertex buffer using a set index buffer
		*	Param _kePrimitiveType	: The type of primitives to render
		*	Param _kuPrimitiveCount	: The number of primitiives to render
		*	Return : Success
		*/
		virtual bool DrawIndexedPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexCount );
		// State changes 

		/*
		*	Sets a transformation on the renderer
		*	Param _kmTransform 		: The matrix that defines the transform
		*	Param _keTransformType  : Defines the type of transform ( ETransform )
		*	Param _kuStage			: The target stage for the transform
		*/
		virtual void SetTransform( const CFMat4x4& _kmTransform, const ETransforms _keTransformType, const uint32 _kuStage ) ;

		/*
		*	Sets a render state on the renderer
		*	Param _keRenderState	: The render state to set
		*	Param _kuValue			: The value to set
		*/
		//template< typename t>
		virtual void SetRenderState( const ERenderStates _keRenderState, const uint32 _kuValue) ;
		
		
		//// Buffered Draw calls

		///*
		//*	Renders primitives from a set vertex buffer
		//*	Param _kePrimitiveType	: The type of primitives to render
		//*	Param _kuPrimitiveCount : The number of primitives to render
		//*	Return : Success
		//*/
		//virtual bool DrawPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount ) = 0;

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
		virtual bool CreateRenderContext( IRendererContext* _pRendererContex );

		/*
		*	Runs the game loop
		*/
		virtual sint32 RunGameLoop( );

		static LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

	//	Managers

		// Returns the instance of the vertex declaration manager
		virtual IVertexDeclarationManager* GetDeclarationManager( ) const ;

		//Returs the instance of the texture manager implementation
		virtual ITextureManager* GetTextureManager( ) const;

		//Returs the instance of the light manager implementation
		virtual ILightManager* GetLightManager( ) const;

		//Returs the instance of the material manager implementation
		virtual IMaterialManager* GetMaterialManager( ) const;

		// Returns the instance of the effect manager implementation
		virtual IEffectManager* GetEffectManager( );

		protected:

			//Initialises OpenGL
			void InitialiseOpenGL( HWND* _hWnd  );

		protected:

		// Renderer context 

		IRendererContext* m_pRendererContext;
		
		uint32 m_uPad[2];
		CFMat4x4 m_mViewMatrix;
		CFMat4x4 m_mWorldMatrix;
		CFMat4x4 m_mProjectionMatrix;
		CFMat4x4 m_mScreenSpaceProjection;
		
		HWND  m_hWnd;
		HDC   m_hDC;
		HGLRC m_hRC;


		//IDirect3DVertexDeclaration9*	m_pDefaultVertexDecl;	//!< The default vertex declaration

		// Managers 

		IVertexDeclarationManager*    m_pDeclManager;	//!< The vetex declaration manager implementation.
		ILightManager*				  m_pLightMngr;
		IMaterialManager*             m_pMaterialMngr;
		//CDX9TextureManager*			  m_pTextureMngr;	//!< The DX texture manager implementation
		//CDX9LightManager*			  m_pLightMngr;		//!< The DX light Manager implementation
		//CDX9MaterialManager*		  m_pMaterialMngr;	//!< The DX Material manager implementation
		//CDX9EffectManager*			  m_pEffectMngr;	//!< The DX Effect Manager implementation


	};
}

#endif //_GLRENDERER_H__Included_1682832923

