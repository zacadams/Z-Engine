/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\RenderEffect.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDEREFFECT_H__Included_1553231764
#define _RENDEREFFECT_H__Included_1553231764

#include "CoreLib/Asset.h"
#include "RendererLib/PrimitiveTypes.h"
//#include <wx/object.h>
namespace ZGE
{	
	class ITexture;
	class IVertexDeclaration;
	class IRenderAsset;
	class CMesh;
	class IVertexBuffer;
	class IIndexBuffer;
	
	// Interface for effect driven rendering
	class IRenderEffect : public CAsset< IRenderEffect >
	{
	public:
		IRenderEffect(void){}
		virtual ~IRenderEffect(void){}
	
				/**
		 *	Initialise the render effect.
		 */
		virtual bool Initialise( ) = 0;

		/**
		 * Renders a render asset using this effect.
		 */
		virtual void Render( const EPrimitiveTypes _kePrimitiveType, void* _pVertices, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride ) = 0;	

		/**
		 * Renders a render asset using this effect.
		 */
		virtual void Render( CMesh* _pMesh ) = 0;	

				/**
		 * Renders a render asset using this effect.
		 */
		virtual void Render( const EPrimitiveTypes _kePrimitiveType, IVertexBuffer* _pVertexBuffer, const uint32 _kuPrimitiveCount ) = 0;


		/**
		 * To be implemented to set up device states for a render effect. 
		 */
		virtual void BeginEffect( ) = 0;
		
		/**
		 * To be implemented to clean up device states after an effect has rendered.
		 */
		virtual void EndEffect( ) = 0; 
		inline IVertexDeclaration* GetVertexDeclaration( ) const{ return m_pVertexDeclaration; }
		inline void SetRenderTargets( ITexture** _ppRenderTargets, const uint32 _kuCount ){m_pRenderTargets = _ppRenderTargets; m_uRenderTargetCount = _kuCount;}
	protected:

		IVertexDeclaration* m_pVertexDeclaration;	//!< The vertex declaration for the object rendered.
		ITexture**			m_pRenderTargets;		//!< Render targets.
		uint32				m_uRenderTargetCount;	//!< Render target count.
	};
}

#endif //_RENDEREFFECT_H__Included_1553231764

