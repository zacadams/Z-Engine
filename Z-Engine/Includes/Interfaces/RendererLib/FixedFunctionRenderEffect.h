/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\FixedFunctionRenderEffect.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _FIXEDFUNCTIONRENDEREFFECT_H__Included_526631575
#define _FIXEDFUNCTIONRENDEREFFECT_H__Included_526631575


#include "RendererLib/RenderEffect.h"

#include <vector>

namespace ZGE
{
	struct SRenderStateTarget
	{
		uint32 uRenderState; //!< The render state.
		uint32 uValue;		 //!< The value to set the render state to.
		uint32 uResetValue;	 //!< The default value to set the render state to when 
	};

	struct STextureStageStateTarget
	{
		uint32 uTextureStageState;
		uint32 uOperation;
		uint32 uValue;
		uint32 uResetValue;
	};
	/**
	 * Fixed function rendere effects.
	 */
	class CFixedFunctionRenderEffect : public IRenderEffect	
	{
	public:
		CFixedFunctionRenderEffect(void);
		~CFixedFunctionRenderEffect(void);

		/**
		 *	Initialise the render effect.
		 */
		virtual bool Initialise( );

		/**
		 * Renders a render asset using this effect.
		 */
		virtual void Render( const EPrimitiveTypes _kePrimitiveType, void* _pVertices, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride );	

								/**
		 * Renders a render asset using this effect.
		 */
		virtual void Render( const EPrimitiveTypes _kePrimitiveType, IVertexBuffer* _pVertexBuffer, const uint32 _kuPrimitiveCount );

				/**
		 * Renders a render asset using this effect.
		 */
		virtual void Render( CMesh* _pMesh );

		/**
		 * To be implemented to set up device states for a render effect. 
		 */
		virtual void BeginEffect( );
		
		/**
		 * To be implemented to clean up device states after an effect has rendered.
		 */
		virtual void EndEffect( ); 

		// Adds a render state target.
		void AddRenderStateTarget( const SRenderStateTarget& _krsRenderStateTarget ); 
		// Adds a texture state target.
		void AddTextureStateTarget( const STextureStageStateTarget& _krsTextureStateTarget );
	protected:
		typedef std::vector< SRenderStateTarget > RenderStateVec;
		RenderStateVec m_vecRenderStateTargets;

		typedef std::vector< STextureStageStateTarget > TextureStateVec;
		TextureStateVec m_vecTextureStateTargets;
	};
}

#endif //_FIXEDFUNCTIONRENDEREFFECT_H__Included_526631575

