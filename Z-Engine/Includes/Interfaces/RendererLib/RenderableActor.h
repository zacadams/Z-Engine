/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderableActor.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERABLEACTOR_H__Included_1757393625
#define _RENDERABLEACTOR_H__Included_1757393625

namespace ZGE
{
	class IRenderAsset;
	class IRenderEffect;
	/**
	 *	Base class for all renderable objects.
	 */
	class CRenderableActor
	{
	public:
		CRenderableActor(void);
		virtual ~CRenderableActor(void);
		/** 
		 *	Sets the renderable actors render effect.
		 *	@param pRenderEffect The effect used to render the actor.
		 */
		void SetRenderEffect( IRenderEffect* pRenderEffect );
		/**
		 *	@returns the actors render effect.
		 */
		 IRenderEffect* GetRenderEffect( ) const;

		/**
		 *	Sets the renderable actors render assets.
		 *	@param _pRenderAssets The render assets.
		 */
		inline void SetRenderAsset( IRenderAsset* _pRenderAsset ){ m_pRenderAsset = _pRenderAsset; }

		/**
		 *	@return The renderable actors render assets.
		 */
		inline IRenderAsset* GetRenderAsset( ) const { return m_pRenderAsset; }

	protected: 
		IRenderAsset*  m_pRenderAsset; //!< The renderable actors render resources / assets.
	};
}

#endif //_RENDERABLEACTOR_H__Included_1757393625

