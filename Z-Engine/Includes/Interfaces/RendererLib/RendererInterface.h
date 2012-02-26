/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\RendererInterface.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERERINTERFACE_H__Included_778058050
#define _RENDERERINTERFACE_H__Included_778058050

#include "RendererLib/PrimitiveTypes.h"
#include "RendererLib/RendererTypes.h"

#include <vector>

namespace ZGE
{
	class CFMat4x4;
	class IRendererContext;
	class IVertexDeclarationManager;
	class ITextureManager;
	class ILightManager;
	class IMaterialManager;
	class IEffectManager;
	class IRenderList;
	class CRenderEffectManager;
	class IVertexBufferManager;
		
	class IRendererInterface
	{
	public:
		
		virtual ~IRendererInterface(void){}

		// User draw calls and basic renderer functionality

		/*
		*	Added to enforce the deletion and clean up of the rendering system 
		*/
		virtual bool ShutDown( ) = 0;

	
		//Clears the back buffer
		virtual void Clear( const uint32 _uColour, float32 f_Depth ) = 0; 

		//Notifies and sets up the renderer for rendering
		virtual bool BeginScene( );

		
		//Ends th scene.
		virtual bool EndScene( );

		/*
		*	Renders an array of user defined primitives
		*	Param _kePrimitiveType	: The type of primitives to render as
		*	Param _kuPrimitiveCount : The number of primitives to render
		*	Param _kuVertexStride	: The sizeof each vertex being rendered
		*	Param _kpVertices		: The array of vertices to render
		*	Retun : Success
		*/
		virtual bool DrawPrimitivesUP(	const EPrimitiveTypes _kePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride, const void* _kpVertices) = 0;

		/*
		*	Renders an array of user defined verticies, using an array of user defines indices
		*	Param _ePrimitiveType	: The type of primitive to render as
		*	Param _kuPrimitiveCount	: The number of primitive to render
		*	Param _kuVertexStride	: The size of each vertex being rendered
		*	Param _pIndices			: The array of indices into the vertex array
		*	Param _pVertices		: The array of vertices to render
		*	Return : Success
		*/
		virtual bool DrawIndexedPrimitivesUP( const EPrimitiveTypes _ePrimitiveType, const uint32  _kuPrimitiveCount, const uint32  _kuVertexStride, const void* _kpIndices, const void* _kpVertices ) = 0;

		// State changes 

		/*
		*	Sets a transformation on the renderer
		*	Param _kmTransform 		: The matrix that defines the transform
		*	Param _keTransformType  : Defines the type of transform ( ETransform )
		*	Param _kuStage			: The target stage for the transform
		*/
		virtual void SetTransform( const CFMat4x4& _kmTransform, const ETransforms _keTransformType, const uint32 _kuStage ) = 0;

		/**
		 *	Param _rmTransform 		: To be populated with the transform.
		 *	Param _keTransformType  : Defines the type of transform ( ETransform )
		 *	Param _kuStage			: The target stage for the transform
		 */
		virtual void GetTransform( CFMat4x4& _rmTransform, const ETransforms _keTransformType, const uint32 _kuStage  ) = 0;


		/*
		*	Sets a render state on the renderer
		*	Param _keRenderState	: The render state to set
		*	Param _kuValue			: The value to set
		*/
		//template< typename t>
		virtual void SetRenderState( const ERenderStates _keRenderState, const uint32 _kuValue) = 0;
		
		
		//// Buffered Draw calls

		/*
		*	Renders primitives from a set vertex buffer
		*	Param _kePrimitiveType	: The type of primitives to render
		*	Param _kuPrimitiveCount : The number of primitives to render
		*	Return : Success
		*/
		virtual bool DrawPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount ) = 0;

		/*
		*	Renders primitives from a set vertex buffer using a set index buffer
		*	Param _kePrimitiveType	: The type of primitives to render
		*	Param _kuPrimitiveCount	: The number of primitiives to render
		*	Return : Success
		*/
		virtual bool DrawIndexedPrimitives( const EPrimitiveTypes _ePrimitiveType, const uint32 _kuPrimitiveCount, const uint32 _kuVertexCount ) = 0;


	// Window creation

		/*
		*	Creates a window and sets up the main game loop
		*/
		virtual bool CreateRenderContext( IRendererContext* _pRendererContex ) = 0;

		/*
		*	Runs the game loop
		*/
		virtual sint32 RunGameLoop( ) = 0;

	//	Managers

		// Returns the instance of the vertex declaration manager
		virtual IVertexDeclarationManager* GetDeclarationManager( ) const = 0;

		//Returns the instance of the texture manager implementation
		virtual ITextureManager* GetTextureManager( ) const = 0;

		//Returns the instance of the light manager implementation
		virtual ILightManager* GetLightManager( ) const = 0;

		//Returns the instance of the material manager implementation
		virtual IMaterialManager* GetMaterialManager( ) const = 0;

		// Returns the instance of the effect manager implementation
		virtual IEffectManager* GetEffectManager( ) = 0;

		// Returns the vertex buffer manager.
		virtual IVertexBufferManager* GetVertexBufferManager( ) = 0;

		// Returns the render effect manager.
		CRenderEffectManager* GetRenderEffectManager( );

		// Adds a render list.
		void AddRenderList( IRenderList* );

		// @return The specified render list.
		IRenderList* GetRenderList( const uint32 _kuRenderListType );

		
	protected:
		
		/*
		*	Calculates the number of vertices to draw based on the primitive type and count, Unindexed 
		*	Param _kePrimitiveType  : The primitive type
		*	Param _kuPrimitiveCount : The number of primitives
		*	Return : The number of vertices to draw 
		*/
		const uint32 CalculateVerticeCount( const EPrimitiveTypes _kePrimitiveType, const uint32 _kuPrimtitveCount );

	protected:
		
		typedef std::vector< IRenderList* > RenderLists;
		RenderLists m_vecRenderLists;
		CRenderEffectManager* m_pRenderEffectMngr; // The render effect manager.
	
	};





}// end namespace 

#endif //_RENDERERINTERFACE_H__Included_778058050

