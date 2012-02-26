/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Renderer.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9RENDERER_H__Included_438548799
#define _DX9RENDERER_H__Included_438548799

#include "RendererLib/RendererInterface.h"
#include "MathLib/FMat4x4.h"
#include <windows.h>

// prototypes

struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DVertexDeclaration9;

namespace ZGE
{
	class IVertexDeclaration;
	class CDX9VertexDeclarationManager;
	class CDX9TextureManager;
	class CFMat4x4;
	class CDX9LightManager;
	class CDX9MaterialManager;
	class CDX9EffectManager;
	class CDX9VertexBufferManager;

	_ALIGNED_PREFIX( 16 )
class CDX9Renderer : public IRendererInterface, public TAligned< 16 >
	{
	public:
		CDX9Renderer(void);
		virtual ~CDX9Renderer(void);

		// User draw calls and basic renderer functionality

		/*
		*	Added to enfore the deletion and clean up of the rendering system 
		*/
		virtual bool ShutDown( );

		
		//Clears the back buffer
		virtual void Clear( const uint32 _uColour, float32 _fDepth ); 

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
		virtual bool DrawPrimitivesUP(		const EPrimitiveTypes _kePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride, const void* _kpVertices) ;

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
		*	Renders an array of quads
		*	Param _kuPrimitiveCount	: The number of primitive to render
		*	Param _kuVertexStride	: The size of each vertex being rendered
		*	Param _pVertices		: The array of vertices to render
		*	Return : Success
		*/
		virtual bool DrawQuadsUP( const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpVertices );

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
		virtual void SetTransform( const CFMat4x4& _kmTransform, const ETransforms _keTransformType, const uint32 _kuStage );

				/**
		 *	Param _rmTransform 		: To be populated with the transform.
		 *	Param _keTransformType  : Defines the type of transform ( ETransform )
		 *	Param _kuStage			: The target stage for the transform
		 */
		virtual void GetTransform( CFMat4x4& _rmTransform, const ETransforms _keTransformType, const uint32 _kuStage  );

		/*
		*	Sets a render state on the renderer
		*	Param _keRenderState	: The render state to set
		*	Param _kuValue			: The value to set
		*/
		//template< typename t>
		virtual void SetRenderState( const ERenderStates _keRenderState, const uint32 _kuValue);


		/*
		*	Creates a windo and sets up the main game loop
		*/
		virtual bool CreateRenderContext( IRendererContext* _pRendererContex );

		/*
		*	Runs the game loop
		*/
		virtual sint32 RunGameLoop( );

		static LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);



	// Managers
		
		// Returns the instance of tehe vertex declaration manager
		virtual IVertexDeclarationManager* GetDeclarationManager( ) const ;

		//Returs the instance of the texture manager implementation
		virtual ITextureManager* GetTextureManager( ) const;

		//Returs the instance of the light manager implementation
		virtual ILightManager* GetLightManager( ) const;

		//Returs the instance of the material manager implementation
		virtual IMaterialManager* GetMaterialManager( ) const;

		// Returns the instance of the effect manager implementation
		virtual IEffectManager* GetEffectManager( );

				// Returns the vertex buffer manager.
		virtual IVertexBufferManager* GetVertexBufferManager( );


		static IDirect3DDevice9* GetDevice( ){ return sm_pDevice; }
	protected:

		/*
		*	Initialise the dirtect x sdk and rendering device
		*/
		void InitialiseDirectX( );

	protected:

		IDirect3D9*		         m_pD3D;		//!< The DirectX sdk interface
		static IDirect3DDevice9* sm_pDevice;	//!< The DirectX renderering device instance

	// Renderer context 

		IRendererContext* m_pRendererContext;

		IDirect3DVertexDeclaration9*	m_pDefaultVertexDecl;	//!< The default vertex declaration

		// Managers 

		CDX9VertexDeclarationManager* m_pDeclManager;	//!< The vetex declaration manager implementation.
		CDX9TextureManager*			  m_pTextureMngr;	//!< The DX texture manager implementation
		CDX9LightManager*			  m_pLightMngr;		//!< The DX light Manager implementation
		CDX9MaterialManager*		  m_pMaterialMngr;	//!< The DX Material manager implementation
		CDX9EffectManager*			  m_pEffectMngr;	//!< The DX Effect Manager implementation
		CDX9VertexBufferManager*	  m_pVertexBufferMngr; //!< The DX vertex buffer manager. 

				CFMat4x4 m_mWorldTransform;
		CFMat4x4 m_mViewTransform;
		CFMat4x4 m_mProjectionTRansform;

	};
}// end namespace

#endif //_DX9RENDERER_H__Included_438548799

