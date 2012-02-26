/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\ShaderRenderEffect.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SHADERRENDEREFFECT_H__Included_2064345918
#define _SHADERRENDEREFFECT_H__Included_2064345918

#include "RendererLib/RenderEffect.h"
namespace ZGE
{
	class IEffect;
	/**
	 *	Shader based render effect.
	 */
	class CShaderRenderEffect : public IRenderEffect
	{
	public:
		CShaderRenderEffect(void);
		~CShaderRenderEffect(void);
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
		virtual void Render( CMesh* _pMesh );

						/**
		 * Renders a render asset using this effect.
		 */
		virtual void Render( const EPrimitiveTypes _kePrimitiveType, IVertexBuffer* _pVertexBuffer, const uint32 _kuPrimitiveCount );

		/**
		 * To be implemented to set up device states for a render effect. 
		 */
		virtual void BeginEffect( );
		
		/**
		 * To be implemented to clean up device states after an effect has rendered.
		 */
		virtual void EndEffect( ); 

		void SetTechnique( const char* _kpcTechnique );
		inline void SetEffect( IEffect* _pEffect ){ m_pEffect = _pEffect; }
	protected:
		IEffect*	m_pEffect;		        //!< The effect instance that contains the shaders used in the effect.
		char        m_pcTechnique[256];          //!< The technique to use.
	};
}

#endif //_SHADERRENDEREFFECT_H__Included_2064345918

